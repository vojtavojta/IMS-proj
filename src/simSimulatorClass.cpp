//
//  simSimulatorClass.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 28/11/2020.
//

#include "simSimulatorClass.hpp"
#include "currentSimTime.hpp"

double _g_curentTime = 0;
const double & current_time = _g_curentTime;


Simulator::Simulator(double sTime, double eTime){
    this->start_time = sTime;
    this->end_time = eTime;
    
//    PriorityQueue::eventQueue = std::make_shared<PriorityQueue>();
    _g_curentTime = sTime;
}

void Simulator::run(){
    while (!PriorityQueue::eventQueue->is_empty()) {
        QueueElement e = PriorityQueue::eventQueue->pop_event();
        if(e->time > this->end_time){
            break;
        }
        if (e->time < this->start_time) {
            continue;
        }
        _g_curentTime = e->time;
        e->behaviour();
    }
}
