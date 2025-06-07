#include "../pch.h"
#include "../include/solve_diff_eq.h"

//rozwi¹zywanie równañ ró¿niczkowych L9, L10



long double DifferentialEquationSolver::euler(long double x, long double h)
{
    return x + h * this->f(x);
}

long double DifferentialEquationSolver::heun(long double x, long double h)
{
    long double k1 = f(x);
    long double k2 = f(x + h * k1);
    return x + h / 2.0 * (k1 + k2);
}

long double DifferentialEquationSolver::midpoint(long double x, long double h)
{
    long double k1 = f(x);
    long double k2 = f(x + h / 2.0 * k1);
    return x + h * k2;
}

long double DifferentialEquationSolver::rungeKutta4(long double x, long double h)
{
	long double k1 = f(x);
	long double k2 = f(x + h / 2.0 * k1);
	long double k3 = f(x + h / 2.0 * k2);
	long double k4 = f(x + h * k3);
	return x + h / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4);
}
