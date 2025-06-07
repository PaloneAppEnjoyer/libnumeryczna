
#include <iostream>
#include <vector>
#include <iomanip>
#include "../test/solve_diff_eq_test.h"
#include "../test/solve_nonlinear_diff_eq_test.h"
#include "../test/simultaneous_equations_test.h"
#include "../test/approximation_test.h"
#include "../test/numeric_integration_test.h"
#include "../test/newton_interpolation_test.h"

#include <locale.h>

using namespace std;

void runTests() {

	cout << "Running tests..." << endl;
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
}

int main() {
	setlocale(LC_CTYPE, "Polish");
	runTests();
	cout << "All tests passed!" << endl;
	return 0;
}