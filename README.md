# Dokumentacja Biblioteki Numerycznej

## Spis treści
1. Wprowadzenie
2. Rozwiązywanie równań różniczkowych
3. Rozwiązywanie równań nieliniowych
4. Aproksymacja funkcji
5. Interpolacja Newtona
6. Całkowanie numeryczne
7. Rozwiązywanie układów równań liniowych
8. Przykłady użycia
9. Wymagania i kompilacja

## Wprowadzenie

Biblioteka numeryczna dostarcza zestaw narzędzi do rozwiązywania problemów matematycznych w sposób numeryczny.Zawiera implementacje algorytmów dla:

- Rozwiązywania równań różniczkowych zwyczajnych
- Znajdowania pierwiastków równań nieliniowych
- Aproksymacji i interpolacji funkcji
- Całkowania numerycznego
- Rozwiązywania układów równań liniowych

Struktura katalogów
- src/ - kod źródłowy biblioteki
- include/ - pliki nagłówkowe
- test/ - testy jednostkowe
- examples/ - przykłady użycia
- build/ - katalog build (tworzony automatycznie)

Biblioteka jest napisana w języku C++ i wykorzystuje nowoczesne podejście obiektowe.

## Rozwiązywanie równań różniczkowych

### Klasa `DifferentialEquationSolver`

Klasa implementuje cztery metody rozwiązywania równań różniczkowych zwyczajnych:

1. Metoda Eulera
2. Metoda Heuna
3. Metoda punktu środkowego
4. Metoda Rungego-Kutty 4. rzędu

#### Metody publiczne

```cpp
long double solve(Types type, double (*func)(double), double initial_value, 
                 double max_iteration_value, double step_size)
```

- `type` - typ metody (EULER, HEUN, MIDPOINT, RUNGE_KUTTA4)
- `func` - wskaźnik do funkcji reprezentującej równanie różniczkowe
- `initial_value` - wartość początkowa
- `max_iteration_value` - maksymalna wartość iteracji
- `step_size` - krok całkowania

#### Przykład użycia

```cpp
double example_func(double x) { return x * x; }

DifferentialEquationSolver solver;
double result = solver.solve(DifferentialEquationSolver::Types::RUNGE_KUTTA4, 
                           example_func, 0.0, 10.0, 0.1);
```

## Rozwiązywanie równań nieliniowych

### Klasa `NonlinearDifferentialEquationSolver`

Klasa implementuje cztery metody znajdowania pierwiastków równań nieliniowych:

1. Metoda bisekcji
2. Metoda Newtona (z analityczną pochodną)
3. Metoda falsi (regula falsi)
4. Metoda siecznych

#### Metody publiczne

```cpp
std::vector<double> solve(Type type, double (*f)(double), double start, double end)
```

- `type` - typ metody (BISECTION, NEWTON_ANALYTIC, FALSI, SECANT)
- `f` - wskaźnik do funkcji, której pierwiastki szukamy
- `start`, `end` - przedział poszukiwań

#### Przykład użycia

```cpp
double example_func(double x) { return x*x - 2; }

NonlinearDifferentialEquationSolver solver;
auto roots = solver.solve(NonlinearDifferentialEquationSolver::Type::BISECTION, 
                         example_func, 0.0, 2.0);
```

## Aproksymacja funkcji

### Klasa `approximation`

Klasa implementuje metodę najmniejszych kwadratów dla aproksymacji wielomianowej.

#### Metody publiczne

```cpp
void least_squares_approximation(std::function<double(double)> f)
```

- `f` - funkcja do aproksymacji

#### Przykład użycia

```cpp
approximation approx(0, 1, 3); // przedział [0,1], wielomian 3 stopnia
approx.least_squares_approximation([](double x) { return sin(x); });
```

## Interpolacja Newtona

### Klasa `Interpolation`

Klasa implementuje interpolację wielomianową metodą Newtona.

#### Metody publiczne

```cpp
double evaluateNewton(double x) const
```

- `x` - punkt, w którym obliczana jest wartość wielomianu interpolacyjnego

#### Przykład użycia

```cpp
std::vector<double> x_vals = {0, 1, 2, 3};
std::vector<double> fx_vals = {0, 1, 4, 9};

Interpolation interp(x_vals, fx_vals);
double result = interp.evaluateNewton(1.5); // wartość w punkcie 1.5
```

## Całkowanie numeryczne

### Klasa `Integration`

Klasa implementuje cztery metody całkowania numerycznego:

1. Metoda prostokątów
2. Metoda trapezów
3. Metoda Simpsona
4. Kwadratura Gaussa-Legendre'a

#### Metody publiczne

```cpp
double integrate(std::function<double(double)> func, double a, double b, 
                int n = 1000, Types type = Types::SIMPSON)
```

- `func` - funkcja do całkowania
- `a`, `b` - granice całkowania
- `n` - liczba podziałów
- `type` - typ metody (SIMPSON, TRAPEZOID, RECTANGLE, GAUSS_LEGENDRE)

#### Przykład użycia

```cpp
Integration integrator;
double result = integrator.integrate([](double x) { return x*x; }, 0, 1, 1000, 
                                   Integration::Types::GAUSS_LEGENDRE);
```

## Rozwiązywanie liniowych układów równań

Biblioteka implementuje rozwiązanie układów równań liniowych metodą rozkładu LU macierzy współczynników.

Metoda działa w następujących krokach:

1. *Rozkład LU*  
   Macierz współczynników A jest rozkładana na iloczyn macierzy dolnotrójkątnej L oraz macierzy górnotrójkątnej U, tak że A = L * U.  
   W trakcie rozkładu sprawdzana jest możliwość przeprowadzenia dekompozycji — w przypadku macierzy osobliwej (zerowy element na diagonali U) proces zostaje przerwany z komunikatem błędu.

2. *Podstawienie do przodu*  
   Rozwiązujemy układ L * y = b, gdzie b to wektor wyrazów wolnych, aby wyznaczyć wektor pośredni y.

3. *Podstawienie do tyłu*  
   Rozwiązujemy układ U * x = y w celu znalezienia wektora rozwiązań x.

4. *Weryfikacja wyniku*  
   Po obliczeniu rozwiązania wykonywane jest sprawdzenie poprawności przez porównanie iloczynu A * x z wektorem b. Różnice poszczególnych elementów są wypisywane na standardowe wyjście.

Metoda jest zaimplementowana z dokładnością do małej wartości EPSILON = 1e-9 przy sprawdzaniu zerowości elementów diagonalnych, co zabezpiecza przed dzieleniem przez zero i błędami numerycznymi.

## Przykłady użycia
### Przykład 1. Rozwiązywanie macierzy metodą LU
```cpp
#include "simultaneous_equations.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<std::vector<double>> A = {
        {4, 3, 0},
        {3, 4, -1},
        {0, -1, 4}
    };
    std::vector<double> b = {24, 30, -24};

    solveEquationSystem solver(A, b);
    std::vector<double> x = solver.solveLU();

    std::cout << "Rozwiązanie układu:" << std::endl;
    for (double val : x) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Przykład 2: Rozwiązywanie równania różniczkowego

```cpp
#include "solve_diff_eq.h"

double func(double x) { return -x; }

int main() {
    DifferentialEquationSolver solver;
    double result = solver.solve(DifferentialEquationSolver::Types::RUNGE_KUTTA4, 
                               func, 1.0, 10.0, 0.01);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

### Przykład 3: Znajdowanie pierwiastków równania nieliniowego

```cpp
#include "solve_nonlinear_diff_eq.h"

double func(double x) { return x*x - 2; }

int main() {
    NonlinearDifferentialEquationSolver solver;
    auto roots = solver.solve(NonlinearDifferentialEquationSolver::Type::BISECTION, 
                            func, 0.0, 2.0);
    std::cout << "Root: " << roots[0] << std::endl;
    return 0;
}
```
### Przykład 4: Obliczanie pola krzywych
```cpp
#include <iostream>
#include <cmath>
#include "../include/numeric_integration.h"

// Funkcja opisująca górną granicę działki (np. pomiary terenowe)
double upperBoundary(double x) {
    return 30.0 + 0.5 * x; // Przykładowa funkcja sinusoidalna
}

// Funkcja opisująca dolną granicę działki (np. prosty wykres liniowy)
double lowerBoundary(double x) {
    return 50.0 + 10.0 * std::sin(x / 10.0); // Przykładowa funkcja liniowa
}

int main() {
    setlocale(LC_CTYPE, "Polish");
    Integration integrator;
    double a = 0.0;   // Początek działki (np. w metrach)
    double b = 100.0; // Koniec działki (np. w metrach)
    int n = 10000;     // Liczba podziałów (im więcej, tym większa dokładność)

    // Oblicz powierzchnię między górną a dolną granicą
    double area = integrator.integrate(
        [](double x) { return upperBoundary(x) - lowerBoundary(x); },
        a, b, n, Integration::Types::TRAPEZOID
    );



    std::cout << "Powierzchnia działki: " << area << " metrów kwadratowych" << std::endl;
    return 0;
}
```




## Wymagania i Kompilacja

### Wymagania systemowe
- System operacyjny: Linux/macOS/Windows (z WSL lub MinGW dla Windows)
- Kompilator: g++ (wspierający standard C++14)
- Narzędzia: make, ar (do budowania biblioteki statycznej)

### Instalacja zależności (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential
```

### Kompilacja projektu
1. Sklonuj repozytorium:
```bash
git clone https://github.com/PaloneAppEnjoyer/libnumeryczna.git
cd libnumeryczna
```

2. Zbuduj projekt (Projekt domyślnie kompiluje się z optymalizacją O2):
```bash
make
```
3.(Opcjonalne) Uruchom testy:
```bash
make test
```

4. (Opcjonalne) Zbuduj i uruchom przykłady:
```bash
make examples
./build/example_nazwa_przykladu
```

5. Czyszczenie projektu:
```bash
make clean
```

## Podsumowanie

Biblioteka numeryczna dostarcza kompleksowy zestaw narzędzi do rozwiązywania podstawowych problemów numerycznych w naukach ścisłych i inżynierii. Dzięki przejrzystemu interfejsowi i implementacji różnych metod dla każdego problemu, użytkownik może wybrać najbardziej odpowiednie rozwiązanie dla swojego zadania.
