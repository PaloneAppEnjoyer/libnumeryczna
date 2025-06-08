#include "../include/approximation.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>

double approximation::monomial(int degree, double x) 
{
    return std::pow(x, degree);
}

double approximation::integrate(std::function<double(double)> func, int n) 
{
    if (n <= 0) n = 10000;  // Default value if invalid
    if (n % 2 == 1) ++n;    // Must be even
    
    double h = (b - a) / static_cast<double>(n);
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i += 2) {
        sum += 4.0 * func(a + i * h);
    }
    for (int i = 2; i < n; i += 2) {
        sum += 2.0 * func(a + i * h);
    }

    return (h / 3.0) * sum;
}

void approximation::least_squares_approximation(std::function<double(double)> f) 
{
    std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1));
    std::vector<double> b_vec(degree + 1);

    // Fill matrix A and vector b
    for (int i = 0; i <= degree; ++i) {
        for (int j = 0; j <= degree; ++j) {
            auto integrand = [=](double x) {
                return monomial(i, x) * monomial(j, x);
            };
            A[i][j] = integrate(integrand);
        }
        b_vec[i] = integrate([=](double x) {
            return f(x) * monomial(i, x);
        });
    }

    // Print the matrix and vector for debugging
    std::cout << std::scientific << std::setprecision(6);
    std::cout << "\nMacierz A:\n";
    for (const auto& row : A) {
        for (double val : row) std::cout << val << " ";
        std::cout << "\n";
    }
    std::cout << "Wektor b: ";
    for (double val : b_vec) std::cout << val << " ";
    std::cout << "\n";

    // Gaussian elimination with partial pivoting
    for (int i = 0; i <= degree; ++i) {
        // Partial pivoting
        int max_row = i;
        for (int k = i + 1; k <= degree; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[max_row][i])) {
                max_row = k;
            }
        }
        
        if (max_row != i) {
            std::swap(A[i], A[max_row]);
            std::swap(b_vec[i], b_vec[max_row]);
        }

        if (std::abs(A[i][i]) < 1e-10) {
            throw std::runtime_error("Macierz jest osobliwa lub prawie osobliwa");
        }

        // Eliminate below current row
        for (int k = i + 1; k <= degree; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j <= degree; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b_vec[k] -= factor * b_vec[i];
        }
    }

    // Back substitution
    std::vector<double> c(degree + 1);
    for (int i = degree; i >= 0; --i) {
        c[i] = b_vec[i];
        for (int j = i + 1; j <= degree; ++j) {
            c[i] -= A[i][j] * c[j];
        }
        c[i] /= A[i][i];
    }

    // Print coefficients
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "\nAproksymowane wspolczynniki:\n";
    for (int i = 0; i <= degree; ++i) {
        std::cout << "c[" << i << "] = " << c[i] << "\n";
    }
}