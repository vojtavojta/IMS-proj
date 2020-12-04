//
//  generatedNumbersStatistics.cpp
//  Run
//
//  Created by Radovan Klembara on 04/12/2020.
//

#include "generatedNumbersStatistics.hpp"
#include <cmath>



    

GeneratedNumberInfo::GeneratedNumberInfo(std::string name){
    this->name = name;
    generated = 0;
    min = INFINITY;
    max = -INFINITY;
    sum = 0;
}

double GeneratedNumberInfo::avg_val(){
    if (generated == 0){
        return 0;
    }
    return sum/generated;
}

double GeneratedNumberInfo::standard_deviation(){
    return sqrt((pow(sum, 2) - generated*pow(this->avg_val(), 2))/(generated - 1));
}


GeneratedNumberStatistics::GeneratedNumberStatistics(){
    this->generated_numbers_info.push_back(GeneratedNumberInfo("Random"));
    this->generated_numbers_info.push_back(GeneratedNumberInfo("Exponential"));
    this->generated_numbers_info.push_back(GeneratedNumberInfo("Normal"));
    this->generated_numbers_info.push_back(GeneratedNumberInfo("Uniform"));
}
    
void GeneratedNumberStatistics::add_value(unsigned short type, double value){
    if (this->generated_numbers_info[type].min > value ) {
        this->generated_numbers_info[type].min = value;
    }
    if (this->generated_numbers_info[type].max < value ) {
        this->generated_numbers_info[type].max = value;
    }
    this->generated_numbers_info[type].generated++;
    this->generated_numbers_info[type].sum += value;
}

void GeneratedNumberStatistics::print_out() {
    *this->file_descriptor << "\nGeneral information about all generated values\n\n";
    for (int i = 0; i < generated_numbers_info.size(); i++) {
        if (generated_numbers_info[i].generated != 0) {
            *this->file_descriptor << "-----------------------------------------------------\n";
            switch (i) {
                case RANDOM:
                    *this->file_descriptor << "| Random numbers:\n";
                    break;
                case EXP:
                    *this->file_descriptor << "| Exponential numbers:\n";
                    break;
                case NORM:
                    *this->file_descriptor << "| Normal numbers:\n";
                    break;
                case UNIFORM:
                    *this->file_descriptor << "| Uniform numbers:\n";
                    break;
                default:
                    break;
            }
            *this->file_descriptor << "=====================================================\n";
            *this->file_descriptor << "| Generated: "<< this->generated_numbers_info[i].generated <<"\n";
            *this->file_descriptor << "| Minimal: "<< this->generated_numbers_info[i].min <<"\n";
            *this->file_descriptor << "| Maximal: "<< this->generated_numbers_info[i].max <<"\n";
            *this->file_descriptor << "| Avarage: "<< this->generated_numbers_info[i].avg_val() <<"\n";
            *this->file_descriptor << "| Standard deviation: "<< this->generated_numbers_info[i].standard_deviation() <<"\n";

        }
    }
    *this->file_descriptor << "=====================================================\n";
}
