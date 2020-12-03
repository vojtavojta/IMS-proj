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


class Error: public std::exception{
    virtual const char* what() const throw(){
        return "Can't open output file\n";
    }
};



struct FacilityInfo {
    long long id;
    unsigned long seized;
    unsigned long released;
    unsigned long left;
public:
    
    FacilityInfo(unsigned long long id);
    void add_seized();
    void add_seized(unsigned long number);
    void add_released();
    void add_released(unsigned long number);
    void add_left();
    void add_left(unsigned long number);
    long long getId();
};


class SimulationStatistics {
    std::ostream* file_descriptor;
    double start_time;
    double end_time;
    std::vector<FacilityInfo> facilities{};
    std::vector<FacilityInfo> resources{};
    long long find_facility(unsigned long id);
    long long find_resource_facility(unsigned long id);
public:
    SimulationStatistics();
    
    void set_output_file(std::string file_name);
    
    void add_facility(unsigned long long id);
    void add_resources(unsigned long long id);
    void print_out();
    
    void add_seized(unsigned long id, bool is_facility);
    void add_seized(unsigned long id, bool is_facility, unsigned long number);
    void add_released(unsigned long id, bool is_facility);
    void add_released(unsigned long id, bool is_facility, unsigned long number);
    void add_left(unsigned long id, bool is_facility);
    void add_left(unsigned long id, bool is_facility, unsigned long number);
};

extern SimulationStatistics* simulation_info;

#endif /* simulationStatistics_hpp */
