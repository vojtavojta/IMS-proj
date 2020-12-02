//
//  facilityClass.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "facilityClass.hpp"
#include <algorithm>


Facility::Facility(std::string name){
    this->name = name;
}


std::shared_ptr<ResourcePromise> Facility::seize_or_reserve(){
    std::shared_ptr<ResourcePromise> promise(new ResourcePromise(1));
    if (!seized && this->promises.empty()) {
        promise->satisfied = true;
        seized = true;
        promise->resource_handler->receive_resources(1);
    } else {
        this->promises.push(promise);
    }
    return promise;
}

void Facility::release(ResourcePromise * promise){
    unsigned long res = promise->resource_handler->give_back_All();
    assert(res == 1);
    this->seized = false;
    if(!this->promises.empty()){
        auto new_prom = this->promises.front();
        this->seized = true;
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



