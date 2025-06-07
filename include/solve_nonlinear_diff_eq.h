#ifndef NONLINEAR_DIFFERENTIAL_EQUATION_SOLVER_H
#define NONLINEAR_DIFFERENTIAL_EQUATION_SOLVER_H
#include <stdexcept> // Dodanie nag³ówka dla std::invalid_argument
#include <vector>

class NonlinearDifferentialEquationSolver {
public:
	NonlinearDifferentialEquationSolver(double epsilon = 1e-6, double max_iter=10000) : epsilon(epsilon), max_iter(max_iter) {};
	enum class Type {
		BISECTION, FALSI, SECANT
	};

	std::vector<double> solve(Type type, double (*f)(double), double start, double end);

private:
	double epsilon; // Domyœlna wartoœæ epsilon
	int max_iter; // Domyœlna maksymalna liczba iteracji
	std::vector<std::vector<double>> find_all_roots(double (*f)(double), double start, double end);
	std::vector<std::pair<double, double>> find_intervals(double (*f)(double), double start, double end);
	std::vector<double> regula_falsi_single(double (*f)(double), double a, double b);
	double bisection(double (*f)(double), double a, double b);
	double secant(double (*f)(double), double x0, double x1);

};


#endif
