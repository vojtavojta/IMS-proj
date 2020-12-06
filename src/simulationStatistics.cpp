//
//  statisticsClass.cpp
//  Run
//
//  Created by Radovan Klembara on 03/12/2020.
//

#include "simulationStatistics.hpp"
#include "facilityClass.hpp"
#include <cassert>



FacilityInfo::FacilityInfo(Facility* fac){
    this->facility = fac;
    seized = 0;
    left = 0;
    released = 0;
    wait_time = 0;
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

unsigned long long FacilityInfo::get_fac_id(){
    return this->facility->get_id();
}

void FacilityInfo::add_wait_time(double time){
    this->wait_time += time;
}

double FacilityInfo::avg_wait_time(){
    if ((this->seized) == 0) {
        return 0;
    }
    return this->wait_time/(this->seized);
}

SimulationStatistics::SimulationStatistics(){}


void SimulationStatistics::remove_last_facility(){
    if (this->facilities.size() > 0) {
        this->facilities.pop_back();
    }
}

void SimulationStatistics::add_facility(Facility* fac){
    this->facilities.push_back(FacilityInfo(fac));
}

void SimulationStatistics::add_resources(Facility* fac){
    this->resources.push_back(FacilityInfo(fac));
}

long long SimulationStatistics::find_facility(unsigned long long id){
    for (unsigned long i = 0; i < this->facilities.size(); i++) {
        if (this->facilities[i].get_fac_id() == id) {
            return i;
        }
    }
    return -1;
}

long long SimulationStatistics::find_resource_facility(unsigned long long id){
    for (unsigned long i = 0; i < this->resources.size(); i++) {
        if (this->resources[i].get_fac_id() == id) {
            return i;
        }
    }
    return -1;
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
        assert(index != -1);
        this->facilities[index].add_left(number);
    } else {
        long long index = find_resource_facility(id);
        assert(index != -1);
        this->resources[index].add_left(number);
    }
}

void SimulationStatistics::add_wait_time(unsigned long id, bool is_facility, double time){
    if (is_facility) {
        long long index = find_facility(id);
        this->facilities[index].add_wait_time(time);
    } else {
        long long index = find_resource_facility(id);
        this->resources[index].add_wait_time(time);
    }
}

double SimulationStatistics::avg_wait_time(unsigned long id, bool is_facility){
    if (is_facility) {
        long long index = find_facility(id);
        return this->facilities[index].avg_wait_time();
    } else {
        long long index = find_resource_facility(id);
        return this->resources[index].avg_wait_time();
    }
}

void  SimulationStatistics::print_out(){
    *this->file_descriptor << "\nSimulation ended at simulation time: "<< current_time <<"\n";
    *this->file_descriptor << "\nInformation about simulation events seizing facilities and resources\n\n";
    *this->file_descriptor << "-----------------------------------------------------\n";
    *this->file_descriptor << "| FACILITIES: "<< this->facilities.size()<< "\n";
    *this->file_descriptor << "|====================================================\n";
    for (unsigned long i = 0; i < this->facilities.size(); i++) {
        *this->file_descriptor << "| ID: " << this->facilities[i].facility->get_id() << " \n";
        *this->file_descriptor << "| Name: " << this->facilities[i].facility->name << " \n";
        *this->file_descriptor << "| Seized: " << this->facilities[i].seized << " \n";
        *this->file_descriptor << "| Released: " << this->facilities[i].released << " \n";
        *this->file_descriptor << "| Timed out: " << this->facilities[i].left << " \n";
        *this->file_descriptor << "| Average waiting time: " << this->facilities[i].avg_wait_time() << " \n";
        *this->file_descriptor << "|====================================================\n";
    }
    *this->file_descriptor << "\n----------------------------------------------------\n";
    *this->file_descriptor << "| Resources: "<< this->resources.size()<<"\n";
    *this->file_descriptor << "|====================================================\n";
    for (unsigned long i = 0; i < this->resources.size(); i++) {
        *this->file_descriptor << "| ID: " << this->resources[i].facility->get_id() << " \n";
        *this->file_descriptor << "| Name: " << this->resources[i].facility->name << " \n";
        *this->file_descriptor << "| Seized: " << this->resources[i].seized << " \n";
        *this->file_descriptor << "| Released: " << this->resources[i].released << " \n";
        *this->file_descriptor << "| Timed out: " << this->resources[i].left << " \n";
        *this->file_descriptor << "| Average waiting time: " << this->resources[i].avg_wait_time() << " \n";
        *this->file_descriptor << "=====================================================\n";
    }
    
}
