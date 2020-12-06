// number_generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "numberGenerator.hpp"

//congruential generator
double Random(void) {
    ix = ix * 69069L + 1; // implicit modulo
    return ix / ((double)ULONG_MAX + 1);
}
//generator exponential distribution
double Exp_Random(double lambda) {
    double result = -1 * lambda * log(Random());
    return result;
}
//generator gaussian distribution - using exclusion method
double Norm_Random(double m, double s) {
    double x, y;
    do
    {
        x = X_For_Norm_Distribution(m,s);
        y = Y_For_Norm_Distribution(m, s);
    } while (y > Norm_Distribution_Function(x,m,s));
    return x;
}
//generator uniform distribution
double Uniform_Random(double min, double max) {
    return (min + (Random() * (max - min)));
}
//function of normal distribution used in Norm_Random
double Norm_Distribution_Function(double x, double m, double s)
{
    static const double sqrt_2pi = 2.506628275;
    double a = (x - m) / s;
    double b = 1 / (s * sqrt_2pi);

    return b / s * exp(-0.5f * a * a);
}
//auxiliary function for Norm_Random - return random number in correcct range
double Y_For_Norm_Distribution(double m, double s) {
   double max = Norm_Distribution_Function(m, m, s);
   return Random() * max;
}
//auxiliary function for Norm_Random - return random number in correcct range
double X_For_Norm_Distribution(double m, double s) {
    double max = m + (SIGMA_MULTIPLE * s);
    double min = m - (SIGMA_MULTIPLE * s);
    return (min + (Random() * (max - min)));

}
//Test for Random
void Test_Random(int number_of_iterations) {
    int n_0 = 0, n_1 = 0, n_2 = 0, n_3 = 0;
    double j;
    for (int i = 0; i < number_of_iterations; i++) {
        j = Random();
        if (j < 0.25) {
            n_0++;
        }
        else if (j < 0.5) {
            n_1++;
        }
        else if (j < 0.75) {
            n_2++;
        }
        else {
            n_3++;
        }

    }
    std::cout << "\nBasic random test: \n-----------------------\n";
    std::cout << n_0 << " " << n_1 << " " << n_2 << " " << n_3 ;

}

//Test for Exp_Random
void Test_Exp_Random(int number_of_iterations, double lambda) {
    int n_0 = 0, n_1 = 0, n_2 = 0, n_3 = 0;
    double sum = 0;
    for (int i = 0; i < number_of_iterations; i++) {
        sum += Exp_Random(lambda);

    }
    double avg = sum / number_of_iterations ;
    std::cout << "\n\nExponential test: \n-----------------------\n";
    std::cout << "average:" << avg << ", with lambda = " << lambda << ", number of iterations = " << number_of_iterations;


}
//Test for Norm_Random
void Test_Norm_Random(int number_of_iterations) {
    double j = 0;
    int coun[20];
    for (int c = 0; c < 20; c++) {
        coun[c] = 0;
    }
    std::cout << "\n\n\n\nNormal test:";
    for (int i = 0; i < number_of_iterations; i++) {
        j = Norm_Random(10, 1);
        for (int c = 0; c < 20; c++) {
            if (j<=c)
            {
                coun[c]++;
                break;
            }
        }
    }
    for (int c = 0; c < 20; c++) {
        std::cout << "\n>" << coun[c];
    }
}
//Test for Uniform_Random
void Test_Uniform_Random(int number_of_iterations) {
    double j = 0;
    int coun[20];
    for (int c = 0; c < 20; c++) {
        coun[c] = 0;
    }
    std::cout << "\n\n\n\nUniform test:";
    for (int i = 0; i < number_of_iterations; i++) {
        j = Uniform_Random(5, 13);
        for (int c = 0; c < 20; c++) {
            if (j <= c)
            {
                coun[c]++;
                break;
            }
        }
    }
    for (int c = 0; c < 20; c++) {
        std::cout << "\n>" << coun[c];
    }
}

//int main()
//{
//    Test_Random(100000);
//    Test_Exp_Random(100000,10);
//    Test_Norm_Random(10000);
//    Test_Uniform_Random(10000);
//    
//    
//    return 0;
//
//}


