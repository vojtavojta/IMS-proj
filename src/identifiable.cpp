//
//  identifiable.cpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#include "identifiable.hpp"

unsigned long long Identifieble::identifier = 0;
    
unsigned long long Identifieble::nextIdentifier() {
    return Identifieble::identifier++;
}

Identifieble::Identifieble(){
    id = Identifieble::nextIdentifier();
}

unsigned long long Identifieble::getId(){
    return this->id;
}
