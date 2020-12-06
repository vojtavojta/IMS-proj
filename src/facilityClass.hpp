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
#include <vector>
#include "simulationStatistics.hpp"
#include "identifiable.hpp"

#define HIGHER_PRIO -1
#define LOWER_PRIO -2

#define TRANSFER_OK 0
#define TRANSFER_NOT_ENOUGH 1
#define TRANSFER_WRONG_SERVICE -1
 
/// Global variable of simulation statistics.
extern SimulationStatistics* simulation_info;

/// Forward declaration of resource promise.
class ResourcePromise;


/// Element of pseudo priority queue.
struct PriorityQueuePromiseElement {
    int priority;
    std::queue<std::shared_ptr<ResourcePromise>> promises {};
    
    /// Constructor of promise priority queue element.
    /// @param priority of promise seizing resource
    PriorityQueuePromiseElement(int priority);
};

/// Class of facility.
class Facility: public std::enable_shared_from_this<Facility>, public Identifiable {
public:
    bool seized = false;
    bool is_facility;
    std::vector<PriorityQueuePromiseElement> queues;
    std::string name;

    /// Constructor of facility.
    /// @param name facility name
    Facility(std::string name);
    
    /// Gets index to pseudo priority queue of queue with certain priority.
    /// @param priority of searched queue
    long get_index_to_queues(int priority);
    
    /// Checks if pseudo priority queue is empty.
    bool is_queues_empty();
    
    /// Gets promise with highest priority from pseudo queue.
    std::shared_ptr<ResourcePromise> get_promise_from_queue();
    
    /// Gets length of queue with lowest priority.
    unsigned long queue_len();
    
    /// Gets length of queue with certain priority.
    /// @param priority of queue
    unsigned long queue_len(int priority);
    
    /// Removes promise from queue.
    void remove_promise(ResourcePromise * promise);
    
    /// Returns resources.
    /// @param number of resources
    virtual void get_back(unsigned long number);
    
    /// Tries to seize resource with default priority(0).
    std::shared_ptr<ResourcePromise> seize_or_reserve();
    
    /// Tries to seize resurce with certain priority.
    /// @param priority of seizing resource
    std::shared_ptr<ResourcePromise> seize_or_reserve(int priority);
    
    /// Inserts promise into pseudo queue.
    /// @param promise to be inserted into queue
    void insert_promise(std::shared_ptr<ResourcePromise> promise);
    
    /// Checks if facility is seized.
    virtual bool busy();
    
    virtual ~Facility() {
        
    }
};

/// Class of resources (Store).
class Resources: public Facility{
private:
    unsigned long current_sources;
    unsigned long capacity;
public:
    
    /// Constructor of resources.
    /// @param name of resources
    /// @param sources capacity of resources
    Resources(std::string name, unsigned long sources);
    
    /// Handles return of some resources.
    /// @param number of returned resources
    void get_back(unsigned long number) override;
    
    /// Tries to seize some resources with default priority(0).
    /// @param source_number number of resources to be seized
    std::shared_ptr<ResourcePromise> seize_or_reserve(unsigned long source_number);
    
    /// Tries to seize some resources with certain priority.
    /// @param source_number number of resources to be seized
    /// @param priority priority of seizing
    std::shared_ptr<ResourcePromise> seize_or_reserve(unsigned long source_number, int priority);
    
    /// Checks if resources are busy.
    bool busy() override;
};


/// Class of resource handler. Handles manipulation of resources.
class ResourceHandler{
    unsigned long req_resources;
    unsigned long current_resources;
public:
    std::shared_ptr<Facility> service_line;
    
    /// Constructor of resource handler.
    /// @param req_resources number of requered resources
    /// @param service_line owning seized resources
    ResourceHandler(unsigned long req_resources, std::shared_ptr<Facility> service_line);
    
    /// Releases all resources.
    void release();
    
    /// Releases number of resources equaling to number given in parameter. If number is higher than
    /// current resources, all current resources will be released.
    /// @param number of resources to be released
    void release(unsigned long number);
    
    /// Transfers number of resources to another resource handler.
    /// @param next_handler another resource handler
    /// @param number of resources to be transferred
    /// @returns TRANSFER_OK if everything was transferred correctly, TRANSFER_NOT_ENOUGH
    /// if number was higher than current resources therefore all resources were transferred instead,
    /// TRANSFER_WRONG_SERVICE if another handler doesnt have resources of same type
    int transfer_to(std::shared_ptr<ResourceHandler> next_handler, unsigned long number);
    
    /// Receives number of resources.
    /// @param number of resources received
    void receive_resources(unsigned long number);
    
    /// Returns number of currently owned resources.
    unsigned long my_resources();
    
    /// Returns number of initial required resources.
    unsigned long required_resources();
};

#endif /* facilityClass_hpp */
