#include <iostream>
#include <omp.h>
using namespace std;

int main() {
	string stringExample = "Search substring in string";
	string substringExample = "ub";

	//Successively
	double t1 = omp_get_wtime();
	int result1 = -1;
	for (int i = 0; i < stringExample.length() - substringExample.length() + 1; i++) {
		int count = 0;
		for (int j = 0; j < substringExample.length(); j++) {
			if (stringExample[i + j] != substringExample[j]) {
				break;
			}
			count++;
		}
		if (count == substringExample.length()) {
			result1 = i;
		}
	}
	double t11 = omp_get_wtime();
	
	cout << "ResultSuccessively = " << result1 << "\n";
	cout << "Running time in sequential mode = " << t11 - t1 << "\n";

	//Parallel
	double t2 = omp_get_wtime();
	int result2 = -1;
	#pragma omp parallel shared(stringExample, substringExample) 
	{
		#pragma omp for
		for (int i = 0; i < stringExample.length() - substringExample.length() + 1; i++) {
			int count = 0;
			for (int j = 0; j < substringExample.length(); j++) {
				if (stringExample[i + j] != substringExample[j]) {
					break;
				}
				count++;
			}
			if (count == substringExample.length()) {
				result2 = i;
			}
		}
	}
	double t22 = omp_get_wtime();
	
	cout << "ResultParallel = " << result2 << "\n";
	cout << "Running time in parallel mode = " << t22 - t2 << "\n";

	system("pause");
	return 0;
}
