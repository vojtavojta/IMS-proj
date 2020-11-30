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
#include "resourceHandler.hpp"

class Resources;

class ResourcePromise: public Identifieble {
    std::weak_ptr<Resources> resources;
    std::shared_ptr<RREvent> success_event{};
    std::shared_ptr<Event> fail_event{};
public:
    std::shared_ptr<ResourceHandler> resource_handler{};
    
    void release();
    
    void on_success(std::shared_ptr<RREvent> event);
    
    void on_success(std::function<void (std::shared_ptr<ResourceHandler>)> succ_handler);
    
    void on_fail(double max_wait, std::function<void ()> fail_handler);
    
    void on_fail(double wait_until, std::shared_ptr<Event> timed_out_event);
    
    // TODO friend
    bool satisfied = false;
    ResourcePromise(unsigned long num_resources);
    void satisfy();
    
};

#endif /* resourcePromiseClass_hpp */
