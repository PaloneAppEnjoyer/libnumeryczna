
#include <iostream>
#include <vector>
#include <iomanip>
#include "../solve_diff_eq_test.h"
using namespace std;

void runTests() {
	cout << "Running tests..." << endl;
	test1();
}

int main() {
	runTests();
	cout << "All tests passed!" << endl;
	return 0;
}