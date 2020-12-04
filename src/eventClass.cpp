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
        tmp->time = t;
        EventPriorityQueue::eventQueue->insert_event(tmp);
    }
}

void Event::plan(){
    this->time = current_time;
    auto tmp = shared_from_this();
    tmp->time = current_time;
    EventPriorityQueue::eventQueue->insert_event(tmp);
}

void Event::terminate(unsigned long ident){
    EventPriorityQueue::eventQueue->delete_event(ident);
}
void Event::terminate(){
    EventPriorityQueue::eventQueue->delete_event(get_id());
}

void Event::behaviour() {}

unsigned long Event::get_id(){
    return this->id;
}


LambdaBasedEvent::LambdaBasedEvent(std::function<void ()> event_behaviour): Event() {
    this->event_behaviour = event_behaviour;
}

void LambdaBasedEvent::behaviour() {
    event_behaviour();
}



RREvent::RREvent(): Event(){}


LambdaBasedRREvent::LambdaBasedRREvent(std::function<void (std::shared_ptr<ResourceHandler> r_handler)> event_behaviour): RREvent(){
    this->event_behaviour = event_behaviour;
}

void LambdaBasedRREvent::behaviour(){
    event_behaviour(this->resource_handler);
}

void RREvent::terminate_with_release(){
    this->terminate();
    this->resource_handler->release();
}

void RREvent::terminate_with_release(std::function<void ()> lambda){
    this->terminate();
    this->resource_handler->release();
    lambda();
}
