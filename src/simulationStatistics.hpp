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
#include "currentSimTime.hpp"

/// Forward declaration of facility.
class Facility;

/// Struct for saving some info about facility.
struct FacilityInfo {
    Facility* facility;
    unsigned long seized;
    unsigned long released;
    unsigned long left;
    double wait_time;
public:
    
    /// Constructor of facility info.
    /// @param fac facility which is watched
    FacilityInfo(Facility* fac);
    
    /// Adds successful seizing of 1 resource.
    void add_seized();
    
    /// Adds successful seizing of certain number of resources.
    /// @param number number of seized resources
    void add_seized(unsigned long number);
    
    /// Adds successful releasing of 1 resource.
    void add_released();
    
    /// Adds successful releasing of certain number of resources.
    /// @param number number of released resources
    void add_released(unsigned long number);
    
    /// Adds 1 resource which couldn't be obtained.
    void add_left();
    
    /// Adds certain number resources which couldn't be obtained.
    /// @param number number of resources
    void add_left(unsigned long number);
    
    /// Adds waiting time.
    /// @param time waiting time
    void add_wait_time(double time);
    
    /// Gets id of facility.
    unsigned long long get_fac_id();
    
    /// Computes avarage waiting time.
    double avg_wait_time();
};


/// Class for saving statistics of all facility/resource objects.
class SimulationStatistics: public Stat {
    std::vector<FacilityInfo> facilities{};
    std::vector<FacilityInfo> resources{};
    long long find_facility(unsigned long long id);
    long long find_resource_facility(unsigned long long id);
public:
    
    /// Constructor of simulation statistics.
    SimulationStatistics();
    
    /// Adds facility.
    /// @param fac facility to be added
    void add_facility(Facility* fac);
    
    /// Removes last added facility.
    void remove_last_facility();
    
    /// Adds resource.
    /// @param fac resource to be added
    void add_resources(Facility* fac);
    
    /// Prints out info.
    void print_out() override;
    
    /// Adds successful seizing of 1 resource.
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    void add_seized(unsigned long id, bool is_facility);
    /// Adds successful seizing of certain number of resources.
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    /// @param number number of seized resources
    void add_seized(unsigned long id, bool is_facility, unsigned long number);
    /// Adds successful releasing of 1 resource.
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    void add_released(unsigned long id, bool is_facility);
    /// Adds successful releasing of certain number of resources.
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    /// @param number number of released resources
    void add_released(unsigned long id, bool is_facility, unsigned long number);
    
    /// Adds 1 resource which couldn't be obtained.
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    void add_left(unsigned long id, bool is_facility);
    
    /// Adds certain number resources which couldn't be obtained.
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    /// @param number number of resources
    void add_left(unsigned long id, bool is_facility, unsigned long number);
    
    /// Adds waiting time.
    /// @param time waiting time
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    void add_wait_time(unsigned long id, bool is_facility,double time);
    
    /// Computes avarage waiting time.
    /// @param id of facility
    /// @param is_facility if service is facility or resources
    double avg_wait_time(unsigned long id, bool is_facility);
};


#endif /* simulationStatistics_hpp */
