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

/// Forward declaration of resource handler.
class ResourceHandler;

/// Forward declaration of facility.
class Facility;

/// Class for promising seize of some facility/resource.
class ResourcePromise: public Identifiable, public std::enable_shared_from_this<ResourcePromise> {
    std::weak_ptr<Facility> resources;
    std::shared_ptr<RREvent> success_event{};
    std::shared_ptr<Event> fail_event;
public:
    std::shared_ptr<ResourceHandler> resource_handler{};
    int priority;
    bool satisfied = false;
    
    /// Constructor of resource promise with default priority(0) in seizing.
    /// @param num_resources number of resources to be seized
    /// @param resources facility/resources owning resources to seized (to be seized)
    ResourcePromise(unsigned long num_resources, std::shared_ptr<Facility> resources);
    
    /// Constructor of resource promise with certain priority in seizing.
    /// @param num_resources number of resources to be seized
    /// @param resources facility/resources owning resources to seized (to be seized)
    /// @param priority of seizing
    ResourcePromise(unsigned long num_resources, std::shared_ptr<Facility> resources, int priority);
    
    /// Remembers event that should be planned if seizing was succesfull.
    /// @param event event to be planned
    void on_success(std::shared_ptr<RREvent> event);
    
    /// Creates and remembers event that should be planned if seizing was successful.
    /// @param succ_handler behaviour of event
    void on_success(std::function<void (std::vector<std::shared_ptr<ResourceHandler>>)> succ_handler);
    
    /// Plans event that declares what happens if seizing was unsuccessful.
    /// @param wait_until waiting time
    /// @param timed_out_event event to be planned
    void on_fail(double wait_until, std::shared_ptr<Event> timed_out_event);
    
    /// Creates and plans event that declares what happens if seizing was unsuccessful.
    /// @param max_wait waiting time
    /// @param fail_handler behaiviour of event
    void on_fail(double max_wait, std::function<void ()> fail_handler);
    
    /// Satifies resource handler and plans event declared in on_success method.
    void satisfy();
    
};

#endif /* resourcePromiseClass_hpp */
