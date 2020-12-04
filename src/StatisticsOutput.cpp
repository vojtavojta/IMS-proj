//
//  StatisticsOutput.cpp
//  Run
//
//  Created by Radovan Klembara on 04/12/2020.
//

#include "StatisticsOutput.hpp"

Stat::Stat(){
    this->file_descriptor = &(std::cout);
}

void Stat::print_out(){}

void Stat::set_output_file(std::string file_name){
    std::ofstream fout;
    fout.open(file_name.c_str());
    if (fout.is_open()) {
        this->file_descriptor = &fout;
    } else {
        throw new Error;
    }
}
