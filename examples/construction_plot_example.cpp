#include <iostream>
#include <cmath>
#include "../include/numeric_integration.h"

// Funkcja opisuj¹ca górn¹ granicê dzia³ki (np. pomiary terenowe)
double upperBoundary(double x) {
    return 30.0 + 0.5 * x; // Przyk³adowa funkcja sinusoidalna
}

// Funkcja opisuj¹ca doln¹ granicê dzia³ki (np. prosty wykres liniowy)
double lowerBoundary(double x) {
    return 50.0 + 10.0 * std::sin(x / 10.0); // Przyk³adowa funkcja liniowa
}

int main() {
    setlocale(LC_CTYPE, "Polish");
    Integration integrator;
    double a = 0.0;   // Pocz¹tek dzia³ki (np. w metrach)
    double b = 100.0; // Koniec dzia³ki (np. w metrach)
    int n = 10000;     // Liczba podzia³ów (im wiêcej, tym wiêksza dok³adnoœæ)

    // Oblicz powierzchniê miêdzy górn¹ a doln¹ granic¹
    double area = integrator.integrate(
        [](double x) { return upperBoundary(x) - lowerBoundary(x); },
        a, b, n, Integration::Types::TRAPEZOID
    );



    std::cout << "Powierzchnia dzia³ki: " << area << " metrów kwadratowych" << std::endl;
    return 0;
}