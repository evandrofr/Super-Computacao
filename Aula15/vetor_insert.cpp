#include <vector>
#include <iostream>
#include <unistd.h>
#include <omp.h>


double conta_complexa(int i) {
	return 2 * i;
}

int main() {
	int N = 100000000; 
	std::vector<double> vec;

	#pragma omp parallel for default(none) shared(vec) shared(N)
	for (int i = 0; i < N; i++) {
		double tmp = conta_complexa(i);
		#pragma omp critical
		{
			vec.push_back(tmp);
		}
	}
	
	// for (int i = 0; i < N; i++) {
	// 	std::cout << i << " ";
	// }
	
	return 0;
}
