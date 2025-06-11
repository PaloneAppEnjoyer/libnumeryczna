#include "../include/simultaneous_equations.h"

using namespace std;

/*
    Mamy prosty obwód składający się z trzech oczek z rezystorami i źródłami napięcia. 
    Korzystając z metody oczkowej, możemy stworzyć układ równań opisujący prądy w oczkach.
*/

/*
    Oczko 1: R1 = 4ohm, R2 = 1ohm,                V1 = 5V
    Oczko 2: R2 = 3ohm, R3 = 1ohm, R4 = 2ohm,     V2 = 3V
    Oczko 3: R4 = 2ohm, R5 = 5ohm.                V3 = 2V 
*/

vector<vector<double>> resistance = 
{
    {5, -1, 0},
    {-1, 6, -2},
    {0, -2, 7}
};

vector<double> voltage = {5, 3, 2};

int main()
{
    setlocale(LC_CTYPE, "Polish");
    solveEquationSystem circuit(resistance, voltage);
    vector<double> currents = circuit.solveLU();
    cout << "Prady w oczkach:\n";
    for(auto i: currents) 
        cout << i << " A\n";
    cin.get();
    return 0;
}