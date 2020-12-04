//
//  generatedNumbersStatistics.hpp
//  Run
//
//  Created by Radovan Klembara on 04/12/2020.
//

#ifndef generatedNumbersStatistics_hpp
#define generatedNumbersStatistics_hpp

#include <iostream>
#include <string>
#include <vector>
#include "StatisticsOutput.hpp"
#include <climits>

#define RANDOM 0
#define EXP 1
#define NORM 2
#define UNIFORM 3


struct GeneratedNumberInfo {
    std::string name;
    unsigned long long generated;
    double min;
    double max;
    double sum;
    
    GeneratedNumberInfo(std::string name);
    double standard_deviation();
    double avg_val();
};

class GeneratedNumberStatistics: public Stat{
public:
    GeneratedNumberStatistics();
    std::vector<GeneratedNumberInfo> generated_numbers_info{};
    void print_out() override;
    
    void add_value(unsigned short type, double value);
    
};


#endif /* generatedNumbersStatistics_hpp */
