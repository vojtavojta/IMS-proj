//
//  eventClass.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "eventClass.hpp"
#include "priorityQueue.hpp"

Event::Event(){
    priority = 0;
}

Event::Event(int priority){
    this->priority = priority;
}

void Event::plan(double t){
    if (t >= current_time) {
        this->time = t;
        auto tmp = shared_from_this();
        EventPriorityQueue::eventQueue->insert_event(tmp);
    }
}

void Event::plan(){
    this->time = current_time;
    auto tmp = shared_from_this();
    EventPriorityQueue::eventQueue->insert_event(tmp);
}

void Event::terminate(unsigned long ident){
    EventPriorityQueue::eventQueue->delete_event(ident);
}
void Event::terminate(){
    EventPriorityQueue::eventQueue->delete_event(get_id());
}

void Event::behaviour() {}



LambdaBasedEvent::LambdaBasedEvent(std::function<void ()> event_behaviour): Event() {
    this->event_behaviour = event_behaviour;
}

void LambdaBasedEvent::behaviour() {
    event_behaviour();
}



RREvent::RREvent(): Event(){}

void RREvent::behaviour() {}

LambdaBasedRREvent::LambdaBasedRREvent(std::function<void (std::vector<std::shared_ptr<ResourceHandler>> r_handler)> event_behaviour): RREvent(){
    this->event_behaviour = event_behaviour;
}

void LambdaBasedRREvent::behaviour(){
    event_behaviour(this->resource_handler);
}

void RREvent::terminate_with_release(){
    this->terminate();
    for (unsigned long i = 0; i < resource_handler.size(); i++) {
        this->resource_handler[i]->release();
    }
    
}

void RREvent::terminate_with_release(std::function<void ()> lambda){
    terminate_with_release();
    lambda();
}
