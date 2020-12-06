//
//  eventClass.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef eventClass_hpp
#define eventClass_hpp

#include <stdio.h>
#include <memory>
#include "currentSimTime.hpp"
#include <algorithm>
#include "identifiable.hpp"
#include "facilityClass.hpp"


class EventPriorityQueue;




/// Event class.
class Event: public std::enable_shared_from_this<Event>, public Identifiable{
public:
    double time;
    int priority;
    
    /// Constructor
    Event();
    
    
    /// Constructor with order priority in main program queue.
    /// @param priority order priority
    Event(int priority);
    
    /// Inserts itself into event queue caledar.
    /// @param t time when should this event will be planned
    void plan(double t);
    
    /// Inserts itself as first event of event queue calendar
    void plan();
    
    /// Behaviour of event. It should be overrided by events.
    virtual void behaviour();
    
    /// Deletes itself from main queue.
    void terminate();
    
    /// Deletes another event from main queue.
    /// @param ident identifier of event
    void terminate(unsigned long ident);
    
    virtual ~Event() {
        
    }
};


/// Constructor of event defined only by lambda function.
class LambdaBasedEvent: public Event {
    std::function<void ()> event_behaviour;
public:
    /// Constructor of class.
    /// @param event_behaviour labda function representing event behaviour
    LambdaBasedEvent(std::function<void ()> event_behaviour);
    
    /// Behaviour of event.
    void behaviour() override;
    
//    virtual ~LambdaBasedEvent() {
//        
//    }
};


/// Class of event with resource.
class RREvent: public Event {
public:
    std::vector<std::shared_ptr<ResourceHandler>> resource_handler{};
    
    /// Constructor of event.
    RREvent();
    
    /// Releases resource and deletes itself from main queue.
    void terminate_with_release();
    
    /// Releases resource and deletes itself from main queue. After that calls labda function.
    /// @param lambda function to be called after deletion
    void terminate_with_release(std::function<void ()> lambda);
    
    /// Behaviour of event.
    void behaviour() override;
    
//    virtual ~RREvent() {
//
//    }
};

/// Event defined by lambda function with resource.
class LambdaBasedRREvent: public RREvent {
    std::function<void (std::vector<std::shared_ptr<ResourceHandler>> r_handler)> event_behaviour;
public:
    /// Constructor of event.
    /// @param event_behaviour behaviour of event
    LambdaBasedRREvent(std::function<void (std::vector<std::shared_ptr<ResourceHandler>> r_handler)> event_behaviour);
    
    /// Behaviour of event.
    void behaviour() override;
//
//    virtual ~LambdaBasedRREvent() {
//
//    }
};

#endif /* eventClass_hpp */
