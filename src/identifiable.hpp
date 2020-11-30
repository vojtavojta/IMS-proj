//
//  identifiable.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef identifiable_hpp
#define identifiable_hpp

class Identifieble{
    static unsigned long long identifier;
public:
    static unsigned long long nextIdentifier();
    
    unsigned long long id;
    
    Identifieble();
    
};

#endif /* identifiable_hpp */
