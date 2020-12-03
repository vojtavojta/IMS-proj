//
//  facilityClass.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "facilityClass.hpp"
#include "resourcePromiseClass.hpp"

Facility::Facility(std::string name){
    this->name = name;
    this->seized = false;
}

bool Facility::busy(){
    if (this->promises.empty()) {
        return false;
    } else {
        return true;
    }
}

unsigned long Facility::queue_len(){
    return this->promises.size();
}

std::shared_ptr<ResourcePromise> Facility::seize_or_reserve(){
    auto ptr_this = shared_from_this();
    auto promise = std::make_shared<ResourcePromise>(1, ptr_this);
    if (!seized && this->promises.empty()) {
        promise->satisfied = true;
        seized = true;
        simulation_info->add_seized(this->getId(), true);
        promise->resource_handler->receive_resources(1);
    } else {
        this->promises.push(promise);
    }
    return promise;
}

void Facility::get_back(unsigned long number){
    assert(number == 1);
    this->seized = false;
    simulation_info->add_released(this->getId(), true);
    if(!this->promises.empty()){
        auto new_prom = this->promises.front();
        this->seized = true;
        simulation_info->add_seized(this->getId(), true);
        new_prom->resource_handler->receive_resources(1);
        this->promises.pop();
        new_prom->satisfy();
    }
}

void Facility::setName(std::string new_name){
    name = new_name;
}

void Facility::remove_promise(ResourcePromise * promise){
    std::queue<std::shared_ptr<ResourcePromise>> new_queue{};
    while (!this->promises.empty()) {
        std::shared_ptr<ResourcePromise> tmp = this->promises.front();
        this->promises.pop();
        if (tmp->id != promise->id) {
            new_queue.push(tmp);
        }
    }
    this->promises = new_queue;
}



Resources::Resources(std::string name, unsigned long sources): Facility(name){
//    this->name = name;
    this->capacity = sources;
    this->current_sources = sources;
}

std::shared_ptr<ResourcePromise> Resources::seize_or_reserve(unsigned long source_number){
    auto ptr_this = shared_from_this();
    std::shared_ptr<ResourcePromise> promise(new ResourcePromise(source_number, ptr_this));
    if (this->current_sources >= source_number && this->promises.empty()) {
        promise->satisfied = true;
        simulation_info->add_seized(this->getId(), false, source_number);
        this->current_sources -= source_number;
        promise->resource_handler->receive_resources(source_number);
    } else {
        this->promises.push(promise);
    }
    return promise;
}

void Resources::get_back(unsigned long number){
    this->current_sources += number;
    simulation_info->add_released(this->getId(), false, number);
    if(!this->promises.empty() && this->promises.front()->resource_handler->my_resources() <= this->current_sources){
        auto new_prom = this->promises.front();
        unsigned long req_res = new_prom->resource_handler->required_resources();
        this->current_sources -= req_res;
        simulation_info->add_seized(this->getId(), false, new_prom->resource_handler->required_resources());
        new_prom->resource_handler->receive_resources(req_res);
        this->promises.pop();
        new_prom->satisfy();
    }
}



ResourceHandler::ResourceHandler(unsigned long req_resources, std::shared_ptr<Facility> service_line){
    this->req_resources = req_resources;
    this->current_resources = 0;
    this->service_line = service_line;
}

void ResourceHandler::release(unsigned long number){
    this->service_line->get_back(number);
    this->req_resources = 0;
}

void ResourceHandler::release(){
    this->service_line->get_back(this->current_resources);
    this->req_resources = 0;
}

bool ResourceHandler::transfer_to(std::shared_ptr<ResourceHandler> next_handler, unsigned long number){
    assert(this->service_line->getId() == next_handler->service_line->getId());
    if (this->current_resources >= number){
        this->current_resources -= number;
        next_handler->receive_resources(number);
        return true;
    } else {
        this->current_resources -= number;
        if (current_resources < 0) {
            next_handler->receive_resources(number - current_resources);
            current_resources = 0;
        }
        return false;
    }
}

void ResourceHandler::receive_resources(unsigned long number){
    this->current_resources = number;
}

unsigned long ResourceHandler::my_resources(){
    return this->current_resources;
}

unsigned long ResourceHandler::required_resources(){
    return this->req_resources;
}
