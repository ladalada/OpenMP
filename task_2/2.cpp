#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
	double DotProductSuccessively = 0.0;
	double DotProductParallel = 0.0;

	int n = 100000;
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
		DotProductSuccessively += v1[i] * v2[i];
	}
	double t11 = omp_get_wtime();

	cout << "DotProductSuccessively = " << DotProductSuccessively << "\n";
	cout << "Running time in sequential mode = " << t11 - t1 << "\n";

	//Parallel
	double t2 = omp_get_wtime();
	#pragma omp parallel for reduction(+:DotProductParallel)
	for (int i = 0; i < n; i++) {
		DotProductParallel += v1[i] * v2[i];
	}
	double t22 = omp_get_wtime();

	cout << "DotProductParallel = " << DotProductParallel << "\n";
	cout << "Running time in parallel mode = " << t22 - t2 << "\n";

	system("pause");
	return 0;
}
