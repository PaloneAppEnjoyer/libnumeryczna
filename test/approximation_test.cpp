#include "approximation_test.h"
#include "../include/approximation.h"

int test11()
{
    try {
        std::cout << "\nTEST 11: f(x) = x^2 + 2x + 1 na [0, 5], stopien 2\n";
        approximation approx(0, 5, 2);
        approx.least_squares_approximation([](double x) {
            return x * x + 2 * x + 1;
        });
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Blad w test11: " << e.what() << "\n";
        return 1;
    }
}

int test12()
{
    try {
        std::cout << "\nTEST 12: f(x) = sin(x) na [2, 2], stopien 2\n";
        approximation approx(2, 2, 2);
        approx.least_squares_approximation([](double x) {
            return std::sin(x);
        });
        std::cerr << "Blad: oczekiwany wyjatek nie zostal rzucony.\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Oczekiwany blad w test12: " << e.what() << "\n";
        return 0;
    }
}
