#include "approximation_test.h"
#include "../include/approximation.h"

int test11()
{
	try {
        std::cout << "\n=== TEST 11: f(x) = e^x na [0, 1], stopień 2 ===\n";
        approximation approx(0, 1, 2);
        approx.least_squares_approximation([](double x) {
            return std::exp(x);
        });
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Błąd w test11: " << e.what() << "\n";
        return 1;
    }
}

int test12()
{
	try {
        std::cout << "\n=== TEST 12: f(x) = sin(x) na [1, 1], stopień 2 ===\n";
        approximation approx(1, 1, 2); 
        approx.least_squares_approximation([](double x) {
            return std::sin(x);
        });
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Oczekiwany błąd w test12: " << e.what() << "\n";
        return 0;
    }
}
