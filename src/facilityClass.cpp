//
//  facilityClass.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "facilityClass.hpp"
#include "resourcePromiseClass.hpp"
#include <iostream>
#include <cassert>

/// Global variable for saving simulation details.
SimulationStatistics* simulation_info = new SimulationStatistics();

PriorityQueuePromiseElement::PriorityQueuePromiseElement(int priority){
    this->priority = priority;
}


Facility::Facility(std::string name){
    this->name = name;
    this->seized = false;
    simulation_info->add_facility(this);
    is_facility = true;
}

bool Facility::busy(){
    if (this->seized) {
        return true;
    } else {
        return false;
    }
}

unsigned long Facility::queue_len(){
    return this->queues[0].promises.size(); 
}

unsigned long Facility::queue_len(int priority){
    for (size_t i = 0; i < this->queues.size(); i++) {
        if (this->queues[i].priority == priority) {
            return queues[i].promises.size();
        }
    }
    return 0;
}

long Facility::get_index_to_queues(int priority){
    for (size_t i = 0; i < this->queues.size(); i++) {
        if (this->queues[i].priority == priority) {
            return i;
        }
    }
    if (this->queues.size() == 0) {
        return HIGHER_PRIO;
    }
    if (this->queues[this->queues.size()-1].priority > priority) {
        return LOWER_PRIO;
    }
    return HIGHER_PRIO;
}

std::shared_ptr<ResourcePromise> Facility::seize_or_reserve(){
    return this->seize_or_reserve(0);
}

void Facility::insert_promise(std::shared_ptr<ResourcePromise> promise) {
    for (size_t i = 0; i < this->queues.size(); i++) {
        if (this->queues[i].priority == promise->priority) {
            this->queues[i].promises.push(promise);
            return;
        } if (this->queues[i].priority > promise->priority) {
            PriorityQueuePromiseElement tmp = PriorityQueuePromiseElement(promise->priority);
            this->queues.insert(queues.begin() + i, tmp);
            return;
        }
    }
    PriorityQueuePromiseElement tmp = PriorityQueuePromiseElement(promise->priority);
    tmp.promises.push(promise);
    this->queues.push_back(tmp);
}

std::shared_ptr<ResourcePromise> Facility::seize_or_reserve(int priority){
    auto ptr_this = shared_from_this();
    auto promise = std::make_shared<ResourcePromise>(1, ptr_this, priority);
    long index = get_index_to_queues(priority);
    if (!seized) {
        if(index == HIGHER_PRIO){
            promise->satisfied = true;
            seized = true;
            simulation_info->add_seized(this->get_id(), true);
            promise->resource_handler->receive_resources(1);
        } else {
            insert_promise(promise);
        }
    } else {
        insert_promise(promise);
    }
    return promise;
}

bool Facility::is_queues_empty(){
    for (unsigned long i = 0; i < queues.size(); i++) {
        if (!this->queues[i].promises.empty()) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<ResourcePromise> Facility::get_promise_from_queue(){
    std::shared_ptr<ResourcePromise> r = this->queues[this->queues.size()-1].promises.front();
    return r;
}

void Facility::pop_promise_from_queue(){
    this->queues[this->queues.size()-1].promises.pop();
}


void Facility::get_back(unsigned long number){
    assert(number == 1);
    this->seized = false;
    simulation_info->add_released(this->get_id(), true);
    if(!this->is_queues_empty()){
        auto new_prom = this->get_promise_from_queue();
        this->seized = true;
        simulation_info->add_seized(this->get_id(), true);
        simulation_info->add_wait_time(this->get_id(), true, current_time - new_prom->time);
        new_prom->resource_handler->receive_resources(1);
        new_prom->satisfy();
    }
}

void Facility::remove_promise(ResourcePromise * promise){
    std::queue<std::shared_ptr<ResourcePromise>> new_queue{};
    long index = this->get_index_to_queues(promise->priority);
    if(index >= 0){
        while (!this->queues[index].promises.empty()) {
            std::shared_ptr<ResourcePromise> tmp = this->queues[index].promises.front();
            this->queues[index].promises.pop();
            if (tmp->id != promise->id) {
                new_queue.push(tmp);
            }
        }
        this->queues[index].promises = new_queue;
    }
}





Resources::Resources(std::string name, unsigned long sources): Facility(name){
    this->capacity = sources;
    this->current_sources = sources;
    simulation_info->add_resources(this);
    simulation_info->remove_last_facility();
    this->is_facility = false;
}

std::shared_ptr<ResourcePromise> Resources::seize_or_reserve(unsigned long source_number){
    return this->seize_or_reserve(source_number, 0);
}

std::shared_ptr<ResourcePromise> Resources::seize_or_reserve(unsigned long source_number, int priority){
    auto ptr_this = shared_from_this();
    auto promise = std::make_shared<ResourcePromise>(source_number, ptr_this, current_time, priority);
    long index = get_index_to_queues(priority);
    if (this->current_sources >= source_number) {
        if(index == HIGHER_PRIO){
            promise->satisfied = true;
            seized = true;
            simulation_info->add_seized(this->get_id(), false, source_number);
            this->current_sources -= source_number;
            promise->resource_handler->receive_resources(source_number);
            simulation_info->add_wait_time(this->get_id(), false, 0);
        } else {
            insert_promise(promise);
        }
    } else {
        insert_promise(promise);
    }
    return promise;
    
}

void Resources::get_back(unsigned long number){
    this->current_sources += number;
    simulation_info->add_released(this->get_id(), false, number);
    if(!this->is_queues_empty()){
        auto new_prom = this->get_promise_from_queue();
        if (new_prom->resource_handler->required_resources() < this->current_sources) {
            unsigned long req_res = new_prom->resource_handler->required_resources();
            this->current_sources -= req_res;
            simulation_info->add_seized(this->get_id(), false, new_prom->resource_handler->required_resources());
            simulation_info->add_wait_time(this->get_id(), false, current_time - new_prom->time);
            new_prom->resource_handler->receive_resources(req_res);
            this->pop_promise_from_queue();
            new_prom->satisfy();
        }
    }
}

bool Resources::busy(){
    if (current_sources < capacity && queues.empty()){
        return false;
    } else {
        return true;
    }
}

ResourceHandler::ResourceHandler(unsigned long req_resources, std::shared_ptr<Facility> service_line){
    this->req_resources = req_resources;
    this->current_resources = 0;
    this->service_line = service_line;
}

void ResourceHandler::release(unsigned long number){
    if (this->current_resources >= number) {
        this->service_line->get_back(number);
        this->current_resources -= number;
    } else {
        this->service_line->get_back(current_resources);
        this->current_resources = 0;
    }
    
}

void ResourceHandler::release(){
    this->service_line->get_back(this->current_resources);
    this->current_resources = 0;
    this->req_resources = 0;
}

int ResourceHandler::transfer_to(std::shared_ptr<ResourceHandler> next_handler, unsigned long number){
    if(this->service_line->get_id() == next_handler->service_line->get_id()){
        if (this->current_resources >= number){
            this->current_resources -= number;
            next_handler->receive_resources(number);
            return TRANSFER_OK;
        } else {
            next_handler->receive_resources(current_resources);
            current_resources = 0;
            return TRANSFER_NOT_ENOUGH;
        }
    }
    return TRANSFER_WRONG_SERVICE;
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

