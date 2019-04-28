#include <iostream>
#include <omp.h>
using namespace std;

int main() {
	int max_threads_num = 10;
	int max_n = 100000;

	cout << "\n" << "Dimention" << "\t" << "Threads number" << "\t" << "Running time" << "\n\n";

	for (int n = 15; n < max_n + 1; n *= 10) {
		int** matrix1 = new int*[n];
		for (int i = 0; i < n; i++) {
			matrix1[i] = new int[n];
			for (int j = 0; j < n; j++) {
				matrix1[i][j] = rand() % 10;
			}
		}

		int** matrix2 = new int*[n];
		for (int i = 0; i < n; i++) {
			matrix2[i] = new int[n];
			for (int j = 0; j < n; j++) {
				matrix2[i][j] = rand() % 10;
			}
		}

		for (int threads_num = 1; threads_num < max_threads_num + 1; threads_num += 2) {
			int** result = new int*[n];
			for (int i = 0; i < n; i++) {
				result[i] = new int[n];
			}

			double t1 = omp_get_wtime();
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					result[i][j] = 0;
				}
			}

			#pragma omp parallel num_threads(threads_num)
			{
				#pragma omp for
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						for (int k = 0; k < n; k++) {
							result[i][j] += matrix1[i][k] * matrix2[k][j];
						}
					}
				}
			}
			double t2 = omp_get_wtime();

			cout << n << "\t\t";
			cout << threads_num << "\t\t";
			cout << t2 - t1 << "\n";

			for (int i = 0; i < n; i++) {
				delete[] result[i];
			}
			delete[] result;
		}

		for (int i = 0; i < n; i++) {
			delete[] matrix1[i];
		}

		for (int i = 0; i < n; i++) {
			delete[] matrix2[i];
		}

		delete[] matrix1;
		delete[] matrix2;

		cout << "\n";
	}
	system("pause");
	return 0;
}
