# Dokumentacja Biblioteki Numerycznej

## Spis treści
1. [Wprowadzenie](#wprowadzenie)
2. [Rozwiązywanie równań różniczkowych](#rozwiązywanie-równań-różniczkowych)
3. [Rozwiązywanie równań nieliniowych](#rozwiązywanie-równań-nieliniowych)
4. [Aproksymacja funkcji](#aproksymacja-funkcji)
5. [Interpolacja Newtona](#interpolacja-newtona)
6. [Całkowanie numeryczne](#całkowanie-numeryczne)
7. [Rozwiązywanie układów równań liniowych](#rozwiązywanie-układów-równań-liniowych)
8. [Przykłady użycia](#przykłady-użycia)
9. [Wymagania i kompilacja](#wymagania-i-kompilacja)

## Wprowadzenie

Biblioteka numeryczna dostarcza zestaw narzędzi do rozwiązywania problemów matematycznych w sposób numeryczny. Zawiera implementacje algorytmów dla:

- Rozwiązywania równań różniczkowych zwyczajnych
- Znajdowania pierwiastków równań nieliniowych
- Aproksymacji i interpolacji funkcji
- Całkowania numerycznego
- Rozwiązywania układów równań liniowych

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

## Rozwiązywanie układów równań liniowych

### Funkcje globalne

Biblioteka dostarcza zestaw funkcji do rozwiązywania układów równań liniowych metodą LU:

```cpp
void luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, 
                    vector<vector<double>>& U, int N)
vector<double> forwardSubstitution(const vector<vector<double>>& L, 
                                 const vector<double>& b, int N)
vector<double> backwardSubstitution(const vector<vector<double>>& U, 
                                  const vector<double>& y, int N)
vector<double> solveLU(vector<vector<double>>& A, vector<double>& b, int N)
```

#### Przykład użycia

```cpp
vector<vector<double>> A = {{4, 3}, {6, 3}};
vector<double> b = {10, 12};
int N = 2;

auto solution = solveLU(A, b, N);
```

## Przykłady użycia

### Przykład 1: Rozwiązywanie równania różniczkowego

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

### Przykład 2: Znajdowanie pierwiastków równania nieliniowego

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

## Wymagania i kompilacja

### Wymagania
- Kompilator C++ z obsługą standardu C++11 lub nowszego
- Biblioteka standardowa C++

### Kompilacja
Biblioteka może być skompilowana z dowolnym projektem C++ poprzez dołączenie odpowiednich plików nagłówkowych i źródłowych. Przykładowa kompilacja z użyciem g++:

```bash
g++ -std=c++11 main.cpp solve_diff_eq.cpp solve_nonlinear_diff_eq.cpp -o program
```

## Podsumowanie

Biblioteka numeryczna dostarcza kompleksowy zestaw narzędzi do rozwiązywania podstawowych problemów numerycznych w naukach ścisłych i inżynierii. Dzięki przejrzystemu interfejsowi i implementacji różnych metod dla każdego problemu, użytkownik może wybrać najbardziej odpowiednie rozwiązanie dla swojego zadania.
