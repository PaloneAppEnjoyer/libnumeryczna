#include "../include/solve_nonlinear_diff_eq.h"
#include <stdexcept> // Dodanie nag³ówka dla std::invalid_argument
#include <vector>
#include <cmath>
#include <limits>
#include <iostream>
using namespace std;

//rozwi¹zywanie równañ nieliniowych L11, L12

std::vector<std::vector<double>> NonlinearDifferentialEquationSolver::find_all_roots(double(*f)(double), double start, double end)
{
    auto intervals = find_intervals(f, start, end);
    std::vector<std::vector<double>> roots;

    for (auto& interval : intervals) {
        auto result = regula_falsi_single(f, interval.first, interval.second);
        if (!isnan(result[0])) {
            roots.push_back({ interval.first, interval.second, result[0], result[1] });
        }
    }

    return roots;
}

std::vector<std::pair<double, double>> NonlinearDifferentialEquationSolver::find_intervals(double(*f)(double), double start, double end)
{

    std::vector<std::pair<double, double>> intervals;
    double step = (end - start) / max_iter;
    double x1 = start;
    double f1 = f(x1);

    for (int i = 1; i <= max_iter; i++) {
        double x2 = start + i * step;
        double f2 = f(x2);

        if (!isnan(f1) && !isnan(f2) && f1 * f2 < 0) {
            intervals.emplace_back(x1, x2);
        }

        x1 = x2;
        f1 = f2;
    }

   return intervals;
}

std::vector<double> NonlinearDifferentialEquationSolver::regula_falsi_single(double(*f)(double), double a, double b)
{
    double fa = f(a);
    double fb = f(b);

    if (isnan(fa) || isnan(fb)) return { NAN };
    if (fa * fb >= 0) return { NAN };

    double c, fc;
    int iter = 0;

    do {
        c = (a * fb - b * fa) / (fb - fa);
        fc = f(c);

        if (isnan(fc)) return { NAN };

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }

        iter++;

    } while (abs(fc) > epsilon && iter < max_iter);

    return { c, fc };
}

double NonlinearDifferentialEquationSolver::newton_analytical(double(*f)(double), double(*df)(double), double x0)
{
    double x = x0;

    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (abs(dfx) < std::numeric_limits<double>::epsilon()) {
            std::cout << "Pochodna bliska zeru - metoda mo¿e nie byæ zbie¿na." << endl;
            return NAN;
        }
        double x_new = x - fx / dfx;

        if (abs(x_new - x) < epsilon) {
            break;
        }

        x = x_new;
    }

    return x;
}

double NonlinearDifferentialEquationSolver::bisection(double(*f)(double), double a, double b)
{
    if (f(a) * f(b) >= 0) {
        std::cout << "Metoda bisekcji nie mo¿e byæ zastosowana na tym przedziale." << endl;
        return NAN;
    }

    double c;
    for (int i = 0; i < max_iter; ++i) {
        c = (a + b) / 2;

        if (abs(b - a) < epsilon) {
            break;
        }

        if (f(c) == 0.0) {
            break;
        }
        else if (f(c) * f(a) < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }

    return c;
}

double NonlinearDifferentialEquationSolver::secant(double(*f)(double), double x0, double x1)
{
    double x_prev = x0;
    double x_curr = x1;


    for (int i = 0; i < max_iter; ++i) {
        double fx_prev = f(x_prev);
        double fx_curr = f(x_curr);

        if (abs(fx_curr - fx_prev) < numeric_limits<double>::epsilon()) {
            std::cout << "Ró¿nica wartoœci funkcji bliska zeru - metoda mo¿e nie byæ zbie¿na." << endl;
            return NAN;
        }

        double x_new = x_curr - fx_curr * (x_curr - x_prev) / (fx_curr - fx_prev);

        if (abs(x_new - x_curr) < epsilon) {
            break;
        }

        x_prev = x_curr;
        x_curr = x_new;
    }

    return x_curr;
}
