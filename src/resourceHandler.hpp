//
//  resourceHandler.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef resourceHandler_hpp
#define resourceHandler_hpp

#include <memory>

class ResourceHandler{
    unsigned long req_resources;
    unsigned long current_resources;
public:
    ResourceHandler(unsigned long req_resources);
    
    unsigned long give_back_All();
    
    bool transfer_to(std::shared_ptr<ResourceHandler> next_handler, unsigned long number);
    
    void receive_resources(unsigned long number);
    
    unsigned long my_resources();

    unsigned long required_resources();
};

#endif /* resourceHandler_hpp */
