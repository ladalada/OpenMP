#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int max_threads_num = 10;
	int max_n = 10000;

	cout << "\n" << "Dimention" << "\t" << "Threads number" << "\t" << "Running time" << "\n\n";

	for (int n = 15; n < max_n + 1; n *= 10)
	{

		int** matrix1 = new int*[n];
		for (int i = 0; i < n; i++)
		{
			matrix1[i] = new int[n];
			for (int j = 0; j < n; j++)
			{
				matrix1[i][j] = rand() % 10;
			}
		}

		int** matrix2 = new int*[n];
		for (int i = 0; i < n; i++)
		{
			matrix2[i] = new int[n];
			for (int j = 0; j < n; j++)
			{
				matrix2[i][j] = rand() % 10;
			}
		}

		for (int threads_num = 1; threads_num < max_threads_num + 1; threads_num += 2)
		{
			int** result = new int*[n];
			for (int i = 0; i < n; i++)
			{
				result[i] = new int[n];
			}

			double t1 = omp_get_wtime();
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					result[i][j] = 0;
				}
			}

#pragma omp parallel num_threads(threads_num)
			{
				int b = omp_get_num_threads();
				int block_size = n / b;
#pragma omp for
				for (int block_num = 0; block_num < b * b; block_num++)
				{
					int i_block = block_num / b;
					int j_block = block_num % b;
					for (int k_block = 0; k_block < b; k_block++)
					{
						for (int i = i_block * block_size; i < (i_block + 1) * block_size; i++)
						{
							for (int j = j_block * block_size; j < (j_block + 1) * block_size; j++)
							{
								for (int k = k_block * block_size; k < (k_block + 1) * block_size; k++)
								{
									result[i][k] += matrix1[i][j] * matrix2[j][k];
								}
							}
						}
					}
				}
			}
			double t2 = omp_get_wtime();

			cout << n << "\t\t";
			cout << threads_num << "\t\t";
			cout << t2 - t1 << "\n";

			for (int i = 0; i < n; i++)
			{
				delete[] result[i];
			}
			delete[] result;
		}

		for (int i = 0; i < n; i++)
		{
			delete[] matrix1[i];
		}

		for (int i = 0; i < n; i++)
		{
			delete[] matrix2[i];
		}

		delete[] matrix1;
		delete[] matrix2;

		cout << "\n";
	}
	system("pause");
	return 0;
}
