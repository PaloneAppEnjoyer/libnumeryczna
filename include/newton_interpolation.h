#include <vector>
#include <stdexcept>
class Interpolation {
private:
    std::vector<double> x_values;
    std::vector<double> fx_values;
    std::vector<double> coefficients;

    void computeNewtonCoefficients(); // oblicza współczynniki
    void validateInput() const {
        for (size_t i = 0; i < x_values.size(); ++i) {
            for (size_t j = i + 1; j < x_values.size(); ++j) {
                if (x_values[i] == x_values[j]) {
                    throw std::invalid_argument("Wartosci X nie moga sie powtarzac.");
                }
            }
        }
    }
public:
	Interpolation(const std::vector<double>& x_vals, const std::vector<double>& fx_vals) : x_values(x_vals), fx_values(fx_vals) {
        validateInput();
		computeNewtonCoefficients();
	}

    double evaluateNewton(double x) const; // wartość wielomianu Newtona dla x
    std::vector<double> getCoefficients() const;
};