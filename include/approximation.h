#pragma once

#ifndef APPROXIMATION_H 
#define APPROXIMATION_H 


#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <fstream>

class approximation
{
    private:
        int a,b, degree;
    public:
    approximation(int A, int B, int DEGREE): a(A), b(B), degree(DEGREE) {
        if (A >= B)
        throw std::invalid_argument("Nieprawidlowy przedzial: a musi byc < b.");
    };
    double monomial(int degree, double x);
    double integrate(std::function<double(double)> func, int n = 10000);
    void least_squares_approximation(std::function<double(double)> f);
};

#endif

