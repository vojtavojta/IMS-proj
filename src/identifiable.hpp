//
//  identifiable.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef identifiable_hpp
#define identifiable_hpp

class Identifiable{
    static unsigned long long identifier;
public:
    static unsigned long long nextIdentifier();
    
    unsigned long long id;
    
    Identifiable();
    unsigned long long get_id();
    
};

#endif /* identifiable_hpp */
