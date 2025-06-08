#include "solve_nonlinear_diff_eq_test.h"
#include "../include/solve_nonlinear_diff_eq.h"
#include <iostream>

using namespace std;
int test3()
{
	NonlinearDifferentialEquationSolver solver;
    double a = 1.0;
    double b = 3.0;
	double root = solver.solve(NonlinearDifferentialEquationSolver::Type::BISECTION, [](double x) {return x * x - 4;}, a, b)[0]; // Zak�adamy, �e metoda zwraca wektor z jednym pierwiastkiem
    double expected = 2.0;

    std::cout << "Test 3 (metoda bisekcji):" << std::endl;
    std::cout << "Oczekiwano: " << expected << std::endl;
    std::cout << "Otrzymano:  " << root << std::endl;

    if (std::abs(root - expected) < 1e-6) {
        std::cout << "Wynik poprawny!" << std::endl;
    }
    else {
        std::cout << "Wynik niepoprawny!" << std::endl;
    }
	return 0;
}

int test4()
{
	double epsilon = 1e-6; // Domy�lna warto�� epsilon

	NonlinearDifferentialEquationSolver solver(epsilon, 2);//2 // Maksymalna liczba iteracji ustawiona na 2, aby wymusi� b��d przy ma�ej liczbie iteracji
    double x0 = 1.0;
    double x1 = 2.0;
	double root = solver.solve(NonlinearDifferentialEquationSolver::Type::SECANT, [](double x) {return x * x * x - x - 2; }, x0, x1)[0]; // Zak�adamy, �e metoda zwraca wektor z jednym pierwiastkiem
    double expected = 1.52138; // Przybli�ony pierwiastek

    std::cout << "Test 4 (metoda siecznych):" << std::endl;
    std::cout << "Oczekiwano: " << expected << std::endl;
    std::cout << "Otrzymano:  " << root << std::endl;

    if (std::abs(root - expected) < 1e-5) {
        std::cout << "Wynik poprawny!" << std::endl;
    }
    else {
        std::cout << "Wynik niepoprawny (spodziewany blad dla malej liczby iteracji)!" << std::endl;
    }
	return 0;
}
