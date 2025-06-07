#include "newton_interpolation_test.h"
#include "../include/newton_interpolation.h"
#include <iostream>
#include <exception>

int test9() {
    try {
        std::cout << "\n=== TEST 9: Interpolacja Newtona dla f(x) = x^2 ===\n";
        std::vector<double> x_vals = {0, 1, 2};
        std::vector<double> fx_vals = {0, 1, 4}; // f(x) = x^2

        Interpolation interp(x_vals, fx_vals);
        double x = 1.5;
        double result = interp.evaluateNewton(x);
        std::cout << "Wartość interpolowanego wielomianu w x = " << x << " wynosi: " << result << "\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Błąd w test9: " << e.what() << "\n";
        return 1;
    }
}

int test10() {
    try {
        std::cout << "\n=== TEST 10: interpolacja (powtarzające się punkty x) ===\n";
        std::vector<double> x_vals = {1, 1, 2}; // powtarzający się x = 1
        std::vector<double> fx_vals = {3, 3, 4};

        Interpolation interp(x_vals, fx_vals); // tu powinno być zgłoszenie wyjątku
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Oczekiwany błąd w test10: " << e.what() << "\n";
        return 0;
    }
}
