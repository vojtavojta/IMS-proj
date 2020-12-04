//
//  facilityClass.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef facilityClass_hpp
#define facilityClass_hpp

#include <string>
#include <queue>
#include <algorithm>
#include "simulationStatistics.hpp"
#include "identifiable.hpp"

extern SimulationStatistics* simulation_info;


class ResourcePromise;


//struct priorityPromiseElement

class Facility: public std::enable_shared_from_this<Facility>, public Identifiable {
private:
    
    bool seized = false;

public:
    bool is_facility;
    std::queue<std::shared_ptr<ResourcePromise>> promises{};
    std::string name;
    
    Facility(std::string name);
    unsigned long queue_len();
    void remove_promise(ResourcePromise *);
    virtual void get_back(unsigned long number);
    std::shared_ptr<ResourcePromise> seize_or_reserve();
    virtual bool busy();
//    friend void ResourcePromise::on_fail(double wait_until, std::shared_ptr<Event> timed_out_event);
//    friend void ResourcePromise::release();
};

class Resources: public Facility{
private:
//    std::queue<std::shared_ptr<ResourcePromise>> promises{};
    unsigned long current_sources;
    unsigned long capacity;
//    std::string name;
//    void remove_promise(ResourcePromise *);
//    void release(ResourcePromise* promise);
public:
    void  get_back(unsigned long number) override;
    std::shared_ptr<ResourcePromise> seize_or_reserve(unsigned long source_number);
    Resources(std::string name, unsigned long sources);
//    void setName(std::string new_name);
    
    
};


class ResourceHandler{
    unsigned long req_resources;
    unsigned long current_resources;
public:
    std::shared_ptr<Facility> service_line;
    
    ResourceHandler(unsigned long req_resources, std::shared_ptr<Facility> service_line);
    
    void release(unsigned long number);
    void release();
    
    bool transfer_to(std::shared_ptr<ResourceHandler> next_handler, unsigned long number);
    
    void receive_resources(unsigned long number);
    
    unsigned long my_resources();

    unsigned long required_resources();
};

#endif /* facilityClass_hpp */
