//
//  simSimulatorClass.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 28/11/2020.
//

#ifndef simSimulatorClass_hpp
#define simSimulatorClass_hpp

#include "priorityQueue.hpp"

class Simulator {
private:
    double start_time;
    double end_time;
public:
    Simulator(double start_time, double end_time);
    void run();
};


#endif /* simSimulatorClass_hpp */
