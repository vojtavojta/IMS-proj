//
//  priorityQueue.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef priorityQueue_hpp
#define priorityQueue_hpp

#include <vector>
 
class Event;

typedef std::shared_ptr<Event> QueueElement;


/// Class for priority queue.
class EventPriorityQueue {
private:
    std::vector<QueueElement> events;
public:
    static std::shared_ptr<EventPriorityQueue> eventiqQueue;
    
    /// Constructor of priority queue
    EventPriorityQueue();
    
    /// Inserts event into queue.
    /// @param event object to be inserted
    void insert_event(QueueElement event);
    
    /// Deletes event from queue.
    /// @param id of event to be deleted
    bool delete_event(unsigned long id);
    
    /// Pops element in front of queue.
    QueueElement pop_event();
    
    QueueElement front_event();
    
    /// Checks if queue is empty.
    bool is_empty();
    
    ~EventPriorityQueue();
};


#endif /* priorityQueue_hpp */
