#ifndef DIFFERENTIAL_EQUATION_SOLVER_H  
#define DIFFERENTIAL_EQUATION_SOLVER_H  

#include <stdexcept> // Dodanie nagłówka dla std::invalid_argument  

class DifferentialEquationSolver {  

public:  
enum class Types  
{  
	EULER, HEUN, MIDPOINT, RUNGE_KUTTA4  
};  
DifferentialEquationSolver() = default;
long double solve(Types type, double (*func)(double), double initial_value, double max_iteration_value, double step_size) {  
	if (step_size <= 0) {  
		throw std::invalid_argument("Step size must be positive.");  
	}  
	if (!func) {  
		throw std::invalid_argument("Function pointer cannot be null.");  
	}  
	this->f = func; // Ustawienie funkcji różniczkowej  
	this->step_size = step_size; // Ustawienie kroku czasowego  
	this->x = initial_value; // Ustawienie wartości początkowej  
	if (max_iteration_value <= 0) {  
		throw std::invalid_argument("Max iteration value must be positive.");  
	}  

	for (long double i = 0; i <= max_iteration_value; i += step_size) {  
		switch (type) {  
		case Types::EULER:  
			x = euler(x, step_size);  
			break;  
		case Types::HEUN:  
			x = heun(x, step_size);  
			break;  
		case Types::MIDPOINT:  
			x = midpoint(x, step_size);  
			break;  
		case Types::RUNGE_KUTTA4:  
			x = rungeKutta4(x, step_size);  
			break;  
		default:  
			throw std::invalid_argument("Unsupported method type.");  
		}  
	}  
	return x; // Zwrócenie końcowej wartości  
}  
private:  
double (*f)(double); // Funkcja różniczkowa  
double step_size; // Krok czasowy  
long double x; // Wartość początkowa  

long double euler(long double x, long double h);  
long double heun(long double x, long double h);  
long double midpoint(long double x, long double h);  
long double rungeKutta4(long double x, long double h);  
};  

#endif
