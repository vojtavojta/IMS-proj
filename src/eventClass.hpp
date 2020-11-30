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
#include "resourceHandler.hpp"

class PriorityQueue;

/// Event class.
class Event: public std::enable_shared_from_this<Event>, public Identifieble{
public:
    double time;

    /// Inserts itself into event queue caledar.
    /// @param t time when should this event will be planned
    void plan(double t);
    
    /// Inserts itself as first event of event queue calendar
    void plan();
    
    virtual void behaviour();
    unsigned long get_id();
    void terminate(unsigned long ident);
    void terminate();
};


class LambdaBasedEvent: public Event {
    std::function<void ()> event_behaviour;
public:
    LambdaBasedEvent(std::function<void ()> event_behaviour);
    void behaviour();
};

class RREvent: public Event {
public:
    std::shared_ptr<ResourceHandler> resource_handler;
    RREvent();
    void behaviour();
};

class LambdaBasedRREvent: public RREvent {
    std::function<void (std::shared_ptr<ResourceHandler> r_handler)> event_behaviour;
public:
    LambdaBasedRREvent(std::function<void (std::shared_ptr<ResourceHandler> r_handler)> event_behaviour);
    void behaviour();
};

#endif /* eventClass_hpp */
