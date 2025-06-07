#include "../pch.h"
#include <vector>

class Interpolation {
private:
    std::vector<double> x_values;
    std::vector<double> fx_values;
    std::vector<double> coefficients;

    void computeNewtonCoefficients(); // oblicza współczynniki

public:
	Interpolation(const std::vector<double>& x_vals, const std::vector<double>& fx_vals) : x_values(x_vals), fx_values(fx_vals) {
		computeNewtonCoefficients();
	}

    double evaluateNewton(double x) const; // wartość wielomianu Newtona dla x
    std::vector<double> getCoefficients() const;
};