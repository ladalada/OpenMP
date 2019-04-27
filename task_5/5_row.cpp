#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int max_threads_num = 10;
	int max_n = 100000;

	cout << "\n" << "Dimention" << "\t" << "Threads number" << "\t" << "Running time" << "\n\n";

	for (int n = 14; n < max_n + 1; n *= 10)
	{
		int** matrix = new int*[n];
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new int[n];
			for (int j = 0; j < n; j++)
			{

				matrix[i][j] = rand() % 10;
			}
		}

		int* vector = new int[n];
		for (int i = 0; i < n; i++)
		{
			vector[i] = rand() % 10;
		}

		for (int threads_num = 1; threads_num < max_threads_num + 1; threads_num += 2)
		{
			int* result = new int[n];
			double t1 = omp_get_wtime();
			for (int i = 0; i < n; i++)
			{
				result[i] = 0;
			}
#pragma omp parallel shared(matrix, vector, result) num_threads(threads_num)
			{
#pragma omp for nowait
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						result[i] += matrix[i][j] * vector[j];
					}
				}
			}
			double t2 = omp_get_wtime();

			cout << n << "\t\t";
			cout << threads_num << "\t\t";
			cout << t2 - t1 << "\n";

			delete[] result;
		}

		for (int i = 0; i < n; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		delete[] vector;

		cout << "\n";
	}
	system("pause");
	return 0;
}
