#include <iostream>
#include <vector>
#include <iomanip>
#include "../include/simultaneous_equations.h"

using namespace std;

int test5()
{
    cout << "\nTEST 5: Poprawny uklad rownan\n";

    vector<vector<double>> A = {
        {2, -1, 1},
        {3, 3, 9},
        {3, 3, 5}
    };

    vector<double> b = {2, -1, 4};

    solveEquationSystem solver(A, b);
    vector<double> result = solver.solveLU();

    cout << "\nRozwiazanie koncowe (x):" << endl;
    for (size_t i = 0; i < result.size(); ++i)
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << result[i] << endl;

    return 0;
}

int test6()
{
    cout << "\nTEST 6: Bledny uklad rownan (macierz osobliwa)\n";

    vector<vector<double>> A = {
        {1, 2, 3},
        {2, 4, 6},
        {3, 6, 9}
    };

    vector<double> b = {6, 12, 18};

    try {
        solveEquationSystem solver(A, b);
        vector<double> result = solver.solveLU();

        cout << "\nRozwiazanie koncowe (x):" << endl;
        for (size_t i = 0; i < result.size(); ++i)
            cout << "x" << i + 1 << " = " << fixed << setprecision(4) << result[i] << endl;
    }
    catch (...) {
        cerr << "\nWystapil wyjatek podczas rozwiazywania ukladu (najprawdopodobniej macierz osobliwa).\n";
    }

    return 0;
}