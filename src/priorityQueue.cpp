//
//  priorityQueue.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "priorityQueue.hpp"

auto __eventQueuePtr = new EventPriorityQueue();
std::shared_ptr<EventPriorityQueue> EventPriorityQueue::eventQueue = std::make_shared<EventPriorityQueue>(*__eventQueuePtr);

EventPriorityQueue::EventPriorityQueue(){
    this->events = std::vector<QueueElement>();
}

void EventPriorityQueue::insert_event(QueueElement event){
    if (events.size() == 0) {
        events.push_back(event);
    } else {
        long long i = 0;
        for (i = events.size()-1; i >= 0; i--) {
            if (events[i]->time >= event->time) {
                if(events[i]->time == event->time){
                    if (events[i]->priority > event->priority) {
                        events.insert(events.begin() + i, event);
                    } else {
                        if (i == (long long) events.size()-1) {
                            events.push_back(event);
                        } else {
                            events.insert(events.begin() + i + 1, event);
                        }
                    }
                } else {
                    if (i == (long long) events.size()-1) {
                        events.push_back(event);
                    } else {
                        events.insert(events.begin() + i + 1, event);
                    }
                }
                break;
            }
        }
        if (i == -1) {
            events.insert(events.begin() + i + 1, event);
        }
    }
}

bool EventPriorityQueue::delete_event(unsigned long id){
    long long index = -1;
    for (int i = 0; i < (long long) events.size(); i++) {
        if (events[i]->get_id() == id) {
            index = i;
            break;
        }
    }
    if (index != -1){
        this->events.erase(this->events.begin() + index);
        return true;
    } else {
        return false;
    }
}

QueueElement EventPriorityQueue::pop_event(){
    QueueElement tmp = this->front_event();
    this->events.pop_back();
    return tmp;
}

QueueElement EventPriorityQueue::front_event(){
    return this->events[this->events.size()-1];
}

bool EventPriorityQueue::is_empty(){
    if (this->events.size() == 0){
        return true;
    } else {
        return false;
    }
}
