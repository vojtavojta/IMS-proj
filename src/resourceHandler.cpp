//
//  resourceHandler.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "resourceHandler.hpp"


ResourceHandler::ResourceHandler(unsigned long req_resources){
    this->req_resources = req_resources;
    this->current_resources = 0;
}

unsigned long ResourceHandler::give_back_All(){
    unsigned long tmp = this->req_resources;
    this->req_resources = 0;
    return tmp;
}

bool ResourceHandler::transfer_to(std::shared_ptr<ResourceHandler> next_handler, unsigned long number){
    if (this->current_resources >= number){
        this->current_resources -= number;
        next_handler->receive_resources(number);
        return true;
    } else {
        this->current_resources -= number;
        if (current_resources < 0) {
            next_handler->receive_resources(number - current_resources);
            current_resources = 0;
        }
        return false;
    }
}

void ResourceHandler::receive_resources(unsigned long number){
    this->current_resources = number;
}

unsigned long ResourceHandler::my_resources(){
    return this->current_resources;
}

unsigned long ResourceHandler::required_resources(){
    return this->req_resources;
}
