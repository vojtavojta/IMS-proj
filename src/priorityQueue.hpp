//
//  priorityQueue.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef priorityQueue_hpp
#define priorityQueue_hpp

#include <vector>
#include "eventClass.hpp"

typedef std::shared_ptr<Event> QueueElement;

class PriorityQueue {
private:
    std::vector<QueueElement> events;
public:
    static std::shared_ptr<PriorityQueue> eventQueue;
    PriorityQueue();
    void insert_event(QueueElement event);
    bool delete_event(unsigned long id);
    QueueElement pop_event();
    QueueElement top_event();
    bool is_empty();
};


#endif /* priorityQueue_hpp */
