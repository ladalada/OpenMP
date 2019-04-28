#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
	int n = 100000;
	double ScalarProductSuccessively = 0.0;
	double ScalarProductParallel = 0.0;

	vector<int> v1;
	for (int i = 0; i < n; i++) {
		int b = rand() % 10 + 1;
		v1.push_back(b);
	}

	vector<int> v2;
	for (int i = 0; i < n; i++) {
		int b = rand() % 10 + 1;
		v2.push_back(b);
	}

	//Successively
	double t1 = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		ScalarProductSuccessively += v1[i] * v2[i];
	}
	double t11 = omp_get_wtime();

	cout << "ScalarProductSuccessivelyy = " << ScalarProductSuccessively << "\n";
	cout << "Running time in sequential mode = " << t11 - t1 << "\n";

	//Parallel
	double t2 = omp_get_wtime();
	#pragma omp parallel for reduction(+:ScalarProductParallel)
	for (int i = 0; i < n; i++) {
		ScalarProductParallel += v1[i] * v2[i];
	}
	double t22 = omp_get_wtime();

	cout << "ScalarProductParallel = " << ScalarProductParallel << "\n";
	cout << "Running time in parallel mode = " << t22 - t2 << "\n";

	system("pause");
	return 0;
}
