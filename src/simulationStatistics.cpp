//
//  statisticsClass.cpp
//  Run
//
//  Created by Radovan Klembara on 03/12/2020.
//

#include "simulationStatistics.hpp"


FacilityInfo::FacilityInfo(unsigned long long id){
    this->id = id;
}

void FacilityInfo::add_seized(){
    this->seized++;
}

void FacilityInfo::add_seized(unsigned long number){
    this->seized+= number;
}

void FacilityInfo::add_released(){
    this->released++;
}

void FacilityInfo::add_released(unsigned long number){
    this->released += number;
}

void FacilityInfo::add_left(){
    this->left++;
}

void FacilityInfo::add_left(unsigned long number){
    this->left += number;
}

long long FacilityInfo::getId(){
    return this->id;
}

SimulationStatistics::SimulationStatistics(){
    this->file_descriptor = &(std::cout);
}

void SimulationStatistics::set_output_file(std::string file_name){
    std::ofstream fout;
    fout.open(file_name.c_str());
    if (fout.is_open()) {
        this->file_descriptor = &fout;
    } else {
        throw new Error;
    }
}

void SimulationStatistics::print_out(){
    
}

void SimulationStatistics::add_facility(unsigned long long id){
    this->facilities.push_back(FacilityInfo(id));
}

void SimulationStatistics::add_resources(unsigned long long id){
    this->resources.push_back(FacilityInfo(id));
}

long long SimulationStatistics::find_facility(unsigned long id){
    for (int i = 0; i > this->facilities.size(); i++) {
        if (this->facilities[i].getId() == id) {
            return i;
        }
    }
    this->facilities.push_back(id);
    return 0;
}

long long SimulationStatistics::find_resource_facility(unsigned long id){
    for (int i = 0; i > this->resources.size(); i++) {
        if (this->resources[i].getId() == id) {
            return i;
        }
    }
    this->resources.push_back(id);
    return 0;
}

void SimulationStatistics::add_seized(unsigned long id, bool is_facility){
    this->add_seized(id, is_facility, 1);
}

void SimulationStatistics::add_seized(unsigned long id, bool is_facility, unsigned long number){
    if (is_facility) {
        long long index = find_facility(id);
        this->facilities[index].add_seized(number);
    } else {
        long long index = find_resource_facility(id);
        this->resources[index].add_seized(number);
    }
}

void SimulationStatistics::add_released(unsigned long id, bool is_facility){
    this->add_released(id, is_facility, 1);
}

void SimulationStatistics::add_released(unsigned long id, bool is_facility, unsigned long number){
    if (is_facility) {
        long long index = find_facility(id);
        this->facilities[index].add_released(number);
    } else {
        long long index = find_resource_facility(id);
        this->resources[index].add_released(number);
    }
}

void SimulationStatistics::add_left(unsigned long id, bool is_facility){
    this->add_left(id, is_facility, 1);
}

void SimulationStatistics::add_left(unsigned long id, bool is_facility, unsigned long number){
    if (is_facility) {
        long long index = find_facility(id);
        assert(index == -1);
        this->facilities[index].add_left(number);
    } else {
        long long index = find_resource_facility(id);
        assert(index == -1);
        this->resources[index].add_left(number);
    }
}

SimulationStatistics* simulation_info = new SimulationStatistics();
