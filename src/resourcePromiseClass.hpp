//
//  resourcePromiseClass.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef resourcePromiseClass_hpp
#define resourcePromiseClass_hpp

#include "eventClass.hpp"
#include "identifiable.hpp"
#include "simulationStatistics.hpp"

class ResourceHandler;
class Facility;

class ResourcePromise: public Identifiable, public std::enable_shared_from_this<ResourcePromise> {
    std::weak_ptr<Facility> resources;
    std::shared_ptr<RREvent> success_event{};
    std::shared_ptr<Event> fail_event;
public:
    std::shared_ptr<ResourceHandler> resource_handler{};
    
//    void release();
    
    void on_success(std::shared_ptr<RREvent> event);
    
    void on_success(std::function<void (std::shared_ptr<ResourceHandler>)> succ_handler);
    
    void on_fail(double max_wait, std::function<void ()> fail_handler);
    
    void on_fail(double wait_until, std::shared_ptr<Event> timed_out_event);
    
    bool satisfied = false;
    ResourcePromise(unsigned long num_resources, std::shared_ptr<Facility> resources);
    void satisfy();
    
};

#endif /* resourcePromiseClass_hpp */
