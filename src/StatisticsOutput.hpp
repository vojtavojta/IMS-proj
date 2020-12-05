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
    Stat();
    virtual void print_out();
    void set_output_file(std::string file_name);
};



#endif /* StatisticsOutput_hpp */
