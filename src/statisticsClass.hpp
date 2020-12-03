//
//  statisticsClass.hpp
//  Run
//
//  Created by Radovan Klembara on 03/12/2020.
//

#ifndef statisticsClass_hpp
#define statisticsClass_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

class FacilityInfo {
    std::string name;
    unsigned long seized;
    unsigned long released;
    unsigned long left;
public:
    FacilityInfo(std::string name);
    void add_seized();
    void add_seized(unsigned long number);
    void add_released();
    void add_released(unsigned long number);
    void add_left();
    void add_left(unsigned long number);
};


class Statistics {
    double start_time;
    double end_time;
    std::vector<std::shared_ptr<FacilityInfo>> facilities;
    std::vector<std::shared_ptr<FacilityInfo>> resources;
public:
    Statistics();
    Statistics(std::string file_name);
    
    void print_out();
};

#endif /* statisticsClass_hpp */
