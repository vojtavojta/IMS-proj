//
//  statisticsClass.hpp
//  Run
//
//  Created by Radovan Klembara on 03/12/2020.
//

#ifndef simulationStatistics_hpp
#define simulationStatistics_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include "StatisticsOutput.hpp"



class Facility;

struct FacilityInfo {
    Facility* facility;
    unsigned long seized;
    unsigned long released;
    unsigned long left;
public:
    FacilityInfo(Facility* fac);
    void add_seized();
    void add_seized(unsigned long number);
    void add_released();
    void add_released(unsigned long number);
    void add_left();
    void add_left(unsigned long number);
    long long get_id();
};


class SimulationStatistics: public Stat {
    double start_time;
    double end_time;
    std::vector<FacilityInfo> facilities{};
    std::vector<FacilityInfo> resources{};
    long long find_facility(unsigned long id);
    long long find_resource_facility(unsigned long id);
public:
    SimulationStatistics();
        
    void add_facility(Facility*);
    void remove_last_facility();
    void add_resources(Facility* );
    
    void print_out() override;
    
    void add_seized(unsigned long id, bool is_facility);
    void add_seized(unsigned long id, bool is_facility, unsigned long number);
    void add_released(unsigned long id, bool is_facility);
    void add_released(unsigned long id, bool is_facility, unsigned long number);
    void add_left(unsigned long id, bool is_facility);
    void add_left(unsigned long id, bool is_facility, unsigned long number);
};


#endif /* simulationStatistics_hpp */
