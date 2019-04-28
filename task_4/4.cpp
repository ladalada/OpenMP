#include <iostream>
#include <omp.h>
using namespace std;

int main() {
	int n = 500, m = 1000;

	int** matrix1 = new int*[n];
	for (int i = 0; i < n; i++) {
		matrix1[i] = new int[m];
		for (int j = 0; j < m; j++) {
			matrix1[i][j] = rand() % 10 + 1;
		}
	}

	int** matrix2 = new int*[m];
	for (int i = 0; i < m; i++) {
		matrix2[i] = new int[n];
		for (int j = 0; j < n; j++) {
			matrix2[i][j] = rand() % 10 + 1;
		}
	}

	int** result1 = new int*[n];
	for (int i = 0; i < n; i++) {
		result1[i] = new int[n];
	}

	int** result2 = new int*[n];
	for (int i = 0; i < n; i++) {
		result2[i] = new int[n];
	}

	//Successively
	double t1 = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result1[i][j] = 0;
			for (int k = 0; k < m; k++) {
				result1[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	double t11 = omp_get_wtime();

	cout << "MatrixMultiplicationSuccessively = " << "\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			cout << result1[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "Running time in sequential mode = " << t11 - t1 << "\n";

	//Parallel
	double t2 = omp_get_wtime();
	#pragma omp parallel shared(matrix1, matrix2)
	{
		for (int i = 0; i < n; i++) {
			#pragma omp for nowait
			for (int j = 0; j < n; j++) {
				result2[i][j] = 0;
				for (int k = 0; k < m; k++) {
					result2[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
	}
	double t22 = omp_get_wtime();

	cout << "MatrixMultiplicationParallel = " << "\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			cout << result2[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "Running time in parallel mode = " << t22 - t2 << "\n";

	for (int i = 0; i < n; i++) {
		delete[] matrix1[i];
	}
	delete[] matrix1;

	for (int i = 0; i < m; i++) {
		delete[] matrix2[i];
	}
	delete[] matrix2;

	for (int i = 0; i < n; i++) {
		delete[] result1[i];
	}
	delete[] result1;

	for (int i = 0; i < n; i++) {
		delete[] result2[i];
	}
	delete[] result2;

	system("pause");
	return 0;
}
