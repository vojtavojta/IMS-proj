//
//  storeClass.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef storeClass_hpp
#define storeClass_hpp

#include <stdio.h>
#include <string>
#include <queue>
#include "resourcePromiseClass.hpp"

class Resources {
private:
    std::queue<std::shared_ptr<ResourcePromise>> promises{};
    unsigned long current_sources;
    unsigned long capacity;
    std::string name;
    void remove_promise(ResourcePromise *);
    void release(ResourcePromise* promise);
public:
    std::shared_ptr<ResourcePromise> seize_or_reserve(unsigned long source_number);
    Resources(std::string name, unsigned long sources);
    void setName(std::string new_name);
    
    friend void ResourcePromise::on_fail(double wait_until, std::shared_ptr<Event> timed_out_event);
    friend void ResourcePromise::release();
};


#endif /* storeClass_hpp */
