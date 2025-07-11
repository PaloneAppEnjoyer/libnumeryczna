#include "../include/simultaneous_equations.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void solveEquationSystem::printMatrix(const vector<vector<double>>& matrix, const string& name, int iteration)
{
    cout << "\n" << name;
    if (iteration != -1) cout << " (po iteracji " << iteration << ")";
    cout << ":\n";
    for (const auto& row : matrix) {
        for (auto val : row)
            cout << setw(10) << setprecision(5) << val << " ";
        cout << endl;
    }
}

void solveEquationSystem::luDecomposition(vector<vector<double>>& L, vector<vector<double>>& U)
{
    L.assign(N, vector<double>(N, 0.0));
    U.assign(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            U[i][j] = A[i][j];
            for (int k = 0; k < i; ++k)
                U[i][j] -= L[i][k] * U[k][j];
        }

        if (fabs(U[i][i]) < EPSILON) {
            cerr << "Blad: Macierz osobliwa - zerowy element diagonalny U w wierszu " << i << "." << endl;
            return; // Przerywamy dalsze obliczenia
        }

        for (int j = i; j < N; ++j) {
            if (i == j) {
                L[i][i] = 1.0;
            } else {
                L[j][i] = A[j][i];
                for (int k = 0; k < i; ++k)
                    L[j][i] -= L[j][k] * U[k][i];
                L[j][i] /= U[i][i];
            }
        }

        printMatrix(L, "Macierz L", i);
        printMatrix(U, "Macierz U", i);
    }
}

vector<double> solveEquationSystem::forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b)
{
    vector<double> y(N, 0.0);
    for (int i = 0; i < N; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j)
            y[i] -= L[i][j] * y[j];
    }

    cout << "\nWektor y (podstawienie do przodu):" << endl;
    for (double val : y)
        cout << setw(10) << setprecision(5) << val << " ";
    cout << endl;

    return y;
}

vector<double> solveEquationSystem::backwardSubstitution(const vector<vector<double>>& U, const vector<double>& y)
{
    vector<double> x(N, 0.0);
    for (int i = N - 1; i >= 0; --i) {
        if (fabs(U[i][i]) < EPSILON) {
            cerr << "Blad: Macierz osobliwa - dzielenie przez zero na diagonali U w wierszu " << i << "." << endl;
            return {}; // Zwracamy pusty wektor
        }
        x[i] = y[i];
        for (int j = i + 1; j < N; ++j)
            x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }

    cout << "\nWektor x (rozwiazanie):" << endl;
    for (double val : x)
        cout << setw(10) << setprecision(5) << val << " ";
    cout << endl;

    return x;
}

vector<double> solveEquationSystem::solveLU()
{
    vector<vector<double>> L, U;
    luDecomposition(L, U);

    // Sprawdzamy, czy L lub U są puste — co oznacza, że wystąpił błąd i LU się nie powiodło
    if (L.empty() || U.empty()) {
        cerr << "Rozwiazywanie ukladu przerwane - LU nie powiodlo sie." << endl;
        return {}; // Pusty wektor
    }

    vector<double> y = forwardSubstitution(L, b);
    vector<double> x = backwardSubstitution(U, y);

    if (x.empty()) {
        cerr << "Rozwiazywanie ukladu przerwane - nie udalo sie uzyskac rozwiazania." << endl;
        return {};
    }

    vector<double> Ax(N, 0.0);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            Ax[i] += A[i][j] * x[j];

    cout << "\nSprawdzenie: Ax vs b\n";
    for (int i = 0; i < N; ++i) {
        cout << "Ax[" << i << "] = " << fixed << setprecision(6) << Ax[i]
             << ", b[" << i << "] = " << b[i]
             << ", roznica = " << fabs(Ax[i] - b[i]) << endl;
    }

    return x;
}
