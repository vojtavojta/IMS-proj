//
//  facilityClass.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef facilityClass_hpp
#define facilityClass_hpp

#include <string>
#include "resourcePromiseClass.hpp"
#include <queue>

class Facility {
private:
    std::queue<std::shared_ptr<ResourcePromise>> promises{};
    std::string name;
    bool seized = false;

public:
    Facility(std::string name);
    
    void remove_promise(ResourcePromise *);
    void release(ResourcePromise* promise);
    std::shared_ptr<ResourcePromise> seize_or_reserve();
    
    void setName(std::string new_name);
    friend void ResourcePromise::on_fail(double wait_until, std::shared_ptr<Event> timed_out_event);
    friend void ResourcePromise::release();
};

#endif /* facilityClass_hpp */
