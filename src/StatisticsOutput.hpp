//
//  StatisticsOutput.hpp
//  Run
//
//  Created by Radovan Klembara on 04/12/2020.
//

#ifndef StatisticsOutput_hpp
#define StatisticsOutput_hpp

#include <iostream>
#include <fstream>

/// Class for output file error.
class Error: public std::exception{
    virtual const char* what() const throw(){
        return "Can't open output file\n";
    }
};

/// Class for stats.
class Stat{
public:
    std::ostream* file_descriptor;
    
    /// Constructor of satatistics class
    Stat();
    
    /// Should print out statistics.
    virtual void print_out();
    
    /// Sets output to file with path in parameter file_name.
    /// @param file_name path to file
    void set_output_file(std::string file_name);
};



#endif /* StatisticsOutput_hpp */
