#include <iostream>
#include <omp.h>
using namespace std;

double f(double x) {
	return (4.0 / (1 + x * x));
}

int main() {
	double IntegralSuccessively = 0.0;
	double IntegralParallelWithoutReduction = 0.0;
	double IntegralParallelWithReduction = 0.0;
	
	double a = 0.0, b = 1.0;
	double h = 0.01;

	double t1 = omp_get_wtime();
	for (int i = 1; i <= 100; i++) {
		IntegralSuccessively += h * f(a + h * (i - 0.5));
	}
	double t11 = omp_get_wtime();

	cout << "IntegralSuccessively = " << IntegralSuccessively << "\n";
	cout << "Running time in sequential mode = " << t11 - t1 << "\n";

	double t2 = omp_get_wtime();
	#pragma omp parallel for
	for (int i = 1; i <= 100; i++) {
		IntegralParallelWithoutReduction += h * f(a + h * (i - 0.5));
	}
	double t22 = omp_get_wtime();

	cout << "IntegralParallelWithoutReduction = " << IntegralParallelWithoutReduction << "\n";
	cout << "Running time in parallel mode without reduction = " << t22 - t2 << "\n";

	double t3 = omp_get_wtime();
	#pragma omp parallel for reduction(+:IntegralParallelWithReduction)
	for (int i = 1; i <= 100; i++) {
		IntegralParallelWithReduction += h * f(a + h * (i - 0.5));
	}
	double t33 = omp_get_wtime();

	cout << "IntegralParallelWithReduction = " << IntegralParallelWithReduction << "\n";
	cout << "Running time in parallel mode with reduction = " << t33 - t3 << "\n";

	system("pause");
	return 0;
}
