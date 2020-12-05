//
//  simSimulatorClass.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 28/11/2020.
//

#ifndef simSimulatorClass_hpp
#define simSimulatorClass_hpp

#include "priorityQueue.hpp"
#include "simulationStatistics.hpp"
#include "generatedNumbersStatistics.hpp"
#include "currentSimTime.hpp"
#include "commonSimulationQueue.hpp"


/// Class for main simulation object which controlls flow of simulation.
class Simulator: public std::enable_shared_from_this<Simulator> {
private:
    double start_time;
    double end_time;
public:
    
    /// Constructor of simulator.
    /// @param start_time start time of simulation
    /// @param end_time ending time of simulation
    Simulator(double start_time, double end_time);
    
    /// Starts simulation.
    void run();
};


#endif /* simSimulatorClass_hpp */
