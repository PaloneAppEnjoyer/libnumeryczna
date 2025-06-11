#include <iostream>
#include <cmath>
#include "../include/numeric_integration.h"

// Funkcja opisuj�ca g�rn� granic� dzia�ki (np. pomiary terenowe)
double upperBoundary(double x) {
    return 30.0 + 0.5 * x; // Przyk�adowa funkcja sinusoidalna
}

// Funkcja opisuj�ca doln� granic� dzia�ki (np. prosty wykres liniowy)
double lowerBoundary(double x) {
    return 50.0 + 10.0 * std::sin(x / 10.0); // Przyk�adowa funkcja liniowa
}

int main() {
    setlocale(LC_CTYPE, "Polish");
    Integration integrator;
    double a = 0.0;   // Pocz�tek dzia�ki (np. w metrach)
    double b = 100.0; // Koniec dzia�ki (np. w metrach)
    int n = 10000;     // Liczba podzia��w (im wi�cej, tym wi�ksza dok�adno��)

    // Oblicz powierzchni� mi�dzy g�rn� a doln� granic�
    double area = integrator.integrate(
        [](double x) { return upperBoundary(x) - lowerBoundary(x); },
        a, b, n, Integration::Types::TRAPEZOID
    );



    std::cout << "Powierzchnia dzia�ki: " << area << " metr�w kwadratowych" << std::endl;
    return 0;
}