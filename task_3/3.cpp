#include <iostream>
#include <omp.h>
using namespace std;

int main() {
	int i, j;
	int n = 500, m = 100;

	int** matrix = new int*[n];
	for (i = 0; i < n; i++) {
		matrix[i] = new int[m];
		for (j = 0; j < m; j++) {
			matrix[i][j] = rand() % 50 + 1;
		}
	}

	//Successively
	int elMin1, elMaxOfMin1 = 0;
	double t1 = omp_get_wtime();
	for (i = 0; i < n; i++) {
		elMin1 = matrix[i][0];
		for (j = 1; j < m; j++) {
			if (matrix[i][j] < elMin1) {
				elMin1 = matrix[i][j];
			}
		}
		if (elMaxOfMin1 < elMin1) {
			elMaxOfMin1 = elMin1;
		}
	}
	double t11 = omp_get_wtime();

	cout << "MaxOfMinSuccessively = " << elMaxOfMin1 << "\n";
	cout << "Running time in sequential mode = " << t11 - t1 << "\n";

	//Parallel
	int elMin2, elMaxOfMin2 = 0;
	double t2 = omp_get_wtime();
	for (i = 0; i < n; i++) {
		elMin2 = matrix[i][0];

		#pragma omp parallel for
		for (j = 1; j < m; j++) {
			if (matrix[i][j] < elMin2) {
				elMin2 = matrix[i][j];
			}
		}
		if (elMaxOfMin2 < elMin2) {
			elMaxOfMin2 = elMin2;
		}
	}
	double t22 = omp_get_wtime();

	cout << "MaxOfMinParallel = " << elMaxOfMin2 << "\n";
	cout << "Running time in parallel mode = " << t22 - t2 << "\n";

	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	system("pause");
	return 0;
}
