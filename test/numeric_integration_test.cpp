#include "numeric_integration_test.h"
#include "../include/numeric_integration.h"
#include <iostream>

int test7()
{
    auto linear_func = [](double x) { return 2 * x; };
    double a = 0.0;
    double b = 1.0;
    int n = 1000; // Du¿a liczba podzia³ów dla dok³adnoœci
	Integration integration;
    double result = integration.integrate(linear_func, a, b, n, Integration::Types::RECTANGLE);
    double expected = 1.0;

    std::cout << "Test 7 (metoda prostok¹tów):" << std::endl;
    std::cout << "Oczekiwano: " << expected << std::endl;
    std::cout << "Otrzymano:  " << result << std::endl;

    if (std::abs(result - expected) < 1e-2) {
        std::cout << "Wynik poprawny!" << std::endl;
    }
    else {
        std::cout << "Wynik niepoprawny!" << std::endl;
    }
    return 0;
}

int test8()
{
    auto quadratic_func = [](double x) { return x * x; };
    double a = 0.0;
    double b = 1.0;
    int n = 1; // Celowo za ma³o podzia³ów

    Integration integration;
    double result = integration.integrate(quadratic_func, a, b, n, Integration::Types::TRAPEZOID);
    double expected = 0.333333;

    std::cout << "Test 8 (metoda trapezów):" << std::endl;
    std::cout << "Oczekiwano: " << expected << std::endl;
    std::cout << "Otrzymano:  " << result << std::endl;

    if (std::abs(result - expected) < 1e-6) {
        std::cout << "Wynik poprawny!" << std::endl;
    }
    else {
        std::cout << "Wynik niepoprawny (spodziewane, bo n=1)!" << std::endl;
    }

    return 0;
}
