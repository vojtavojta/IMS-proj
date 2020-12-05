//
//  simSimulatorClass.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 28/11/2020.
//

#include "simSimulatorClass.hpp"
#include "eventClass.hpp"

double _g_curentTime = 0;
const double & current_time = _g_curentTime;


Simulator::Simulator(double sTime, double eTime){
    this->start_time = sTime;
    this->end_time = eTime;
    
    _g_curentTime = sTime;
}

void Simulator::run(){
    while (!eventQueue->is_empty()) {
        auto e = eventQueue->pop_event();
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
