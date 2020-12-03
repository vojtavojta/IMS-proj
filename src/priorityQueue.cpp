//
//  priorityQueue.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "priorityQueue.hpp"

std::shared_ptr<PriorityQueue> PriorityQueue::eventQueue = std::shared_ptr<PriorityQueue>(new PriorityQueue());

PriorityQueue::PriorityQueue(){
    this->events = std::vector<QueueElement>();
}

void PriorityQueue::insert_event(QueueElement event){
    if (events.size() == 0) {
        events.push_back(event);
    } else {
        long long i = 0;
        for (i = events.size()-1; i >= 0; i--) {
            if (events[i]->time >= event->time) {
                if (i == events.size()-1) {
                    events.push_back(event);
                } else {
                    events.insert(events.begin() + i + 1, event);
                }
                break;
            }
        }
        if (i == -1) {
            events.insert(events.begin() + i + 1, event);
        }
        
    }
}

bool PriorityQueue::delete_event(unsigned long id){
    int index = -1;
    for (int i = 0; i < events.size(); i++) {
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

QueueElement PriorityQueue::pop_event(){
    QueueElement tmp = this->top_event();
    this->events.pop_back();
    return tmp;
}

QueueElement PriorityQueue::top_event(){
    return this->events[this->events.size()-1];
}

bool PriorityQueue::is_empty(){
    if (this->events.size() == 0){
        return true;
    } else {
        return false;
    }
}
