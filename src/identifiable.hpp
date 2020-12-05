//
//  identifiable.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 29/11/2020.
//

#ifndef identifiable_hpp
#define identifiable_hpp

/// Class for identifying objects of some classes.
class Identifiable{
    static unsigned long long identifier;
public:
    unsigned long long id;
    
    /// Constructor of this class.
    Identifiable();
    
    /// Gets new identifier.
    static unsigned long long nextIdentifier();
    
    /// Gets identifier of object.
    unsigned long long get_id();
    
};

#endif /* identifiable_hpp */
