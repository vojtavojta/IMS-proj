//
//  resourcePromiseClass.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "resourcePromiseClass.hpp"
#include "facilityClass.hpp"


ResourcePromise::ResourcePromise(unsigned long num_resources, std::shared_ptr<Facility> resources) {
    auto handler = new ResourceHandler(num_resources, resources);
    this->resource_handler = std::make_shared<ResourceHandler>(*handler);
    this->resources = resources;
    this->priority = 0;
}

ResourcePromise::ResourcePromise(unsigned long num_resources, std::shared_ptr<Facility> resources, int priority) {
    auto handler = new ResourceHandler(num_resources, resources);
    this->resource_handler = std::make_shared<ResourceHandler>(*handler);
    this->resources = resources;
    this->priority = priority;
}

void ResourcePromise::satisfy() {
    this->satisfied = true;
    fail_event->terminate();
    this->success_event->plan();
}

void ResourcePromise::on_success(std::shared_ptr<RREvent> event){
    event->resource_handler.push_back(resource_handler);
    if (satisfied) {
        if (fail_event != nullptr){
            fail_event->terminate();
        }
        event->behaviour();
    } else {
        this->success_event = event;
    }
}

void ResourcePromise::on_success(std::function<void (std::vector<std::shared_ptr<ResourceHandler>>)> succ_handler){
    std::shared_ptr<RREvent> succ_event(new LambdaBasedRREvent(succ_handler));
    on_success(succ_event);
}

void ResourcePromise::on_fail(double max_wait, std::function<void ()> fail_handler) {
    std::shared_ptr<Event> fail_event(new LambdaBasedEvent(fail_handler));
    on_fail(max_wait, fail_event);
}

void ResourcePromise::on_fail(double wait_until, std::shared_ptr<Event> timed_out_event) {
    if (satisfied) {
        return;
    }
    fail_event = std::shared_ptr<Event>(new LambdaBasedEvent([timed_out_event, this]() {
        if(auto resources = this->resources.lock()) {
            simulation_info->add_left(resource_handler->service_line->get_id(), resource_handler->service_line->is_facility);
            resources->remove_promise(this);
        }
        timed_out_event->behaviour();
    }));
    fail_event->plan(current_time + wait_until);
};

//void ResourcePromise::release() {
//    if(auto resources = this->resources.lock()) {
//        resources->release(this);
//    }
//}
