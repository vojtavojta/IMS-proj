//
//  numberGenerator.hpp
//  SimSimLib
//
//  Created by Radovan Klembara on 03/12/2020.
//

#ifndef numberGenerator_hpp
#define numberGenerator_hpp
#include "generatedNumbersStatistics.hpp"

static unsigned long ix = 2; // seed
static double SIGMA_MULTIPLE = 100;// determines accuracy of Norm_Random

double Random(void);
double Exp_Random(double lambda);
double Norm_Random(double m, double s);
double Uniform_Random(double min, double max);


double Norm_Distribution_Function(double x, double m, double s);
double X_For_Norm_Distribution(double m, double s);
double Y_For_Norm_Distribution(double m, double s);

void Test_Random(int number_of_iterations);
void Test_Exp_Random(int number_of_iterations, double lambda);
void Test_Norm_Random(int number_of_iterations);
void Test_Uniform_Random(int number_of_iterations);

#endif /* numberGenerator_hpp */
