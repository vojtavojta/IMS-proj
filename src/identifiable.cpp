//
//  identifiable.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "identifiable.hpp"

unsigned long long Identifiable::identifier = 0;
    
unsigned long long Identifiable::nextIdentifier() {
    return Identifiable::identifier++;
}

Identifiable::Identifiable(){
    id = Identifiable::nextIdentifier();
}

unsigned long long Identifiable::get_id(){
    return this->id;
}
