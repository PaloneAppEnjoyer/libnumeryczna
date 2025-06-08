#include "solve_diff_eq_test.h"
#include "../include/solve_diff_eq.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

 double f( double x) {
    return x;
}

int test1()
{
	
    DifferentialEquationSolver solver;
    long double y = 3299;  // Warunek początkowy y(0)=1
    long double h = 0.1;  // Krok całkowania
    long double result = solver.solve(DifferentialEquationSolver::Types::MIDPOINT, [](double x) { return -(9 * pow(10, -12)) * pow(x, 4); }, y, 3299, h);
    long double expected = 223.890235;  // e^(-0.1) ≈ 0.904837

    std::cout << std::fixed;

    std::cout << "Test 1 (metoda Midpoint):" << std::endl;
    std::cout << "Oczekiwano: " << expected << std::endl;
    std::cout << "Otrzymano:  " << result << std::endl;

    if (std::abs(result - expected) < 1e-2) {
        std::cout << "Wynik poprawny!" << std::endl;
    }
    else {
        std::cout << "Wynik niepoprawny!" << std::endl;
        std::cout << "Roznica: " << std::abs(result - expected) << std::endl;
    }
    return 0;
}

int test2()
{
    DifferentialEquationSolver solver;
    long double x = 1.0;
    long double h = 0.5;
	long double result = solver.solve(DifferentialEquationSolver::Types::HEUN, f, x, 1, h);
    long double expected = 1.34375;

    std::cout << "Test 2 (metoda Heuna):" << std::endl;
    std::cout << "Oczekiwano: " << expected << std::endl;
    std::cout << "Otrzymano:  " << result << std::endl;

    if (std::abs(result - expected) < 1e-6) {
        std::cout << "Wynik poprawny!" << std::endl;
    }
    else {
        std::cout << "Wynik niepoprawny (spodziewany blad dla duzego kroku)!" << std::endl;
    }
    return 0;
}
