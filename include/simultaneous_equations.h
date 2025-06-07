#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPSILON = 1e-9;

class solveEquationSystem
{
private:
    vector<vector<double>> A;
    vector<double> b;
    int N;
public:
    solveEquationSystem(const vector<vector<double>>& matrix, const vector<double>& rhs)
        : A(matrix), b(rhs), N(matrix.size()) {}

    void printMatrix(const vector<vector<double>>& matrix, const string& name, int iteration = -1);

    void luDecomposition(vector<vector<double>>& L, vector<vector<double>>& U);

    vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b);

    vector<double> backwardSubstitution(const vector<vector<double>>& U, const vector<double>& y);

    vector<double> solveLU();  // Teraz bez parametrów, korzysta z pól klasy
};