#include <iostream>
#include <algorithm>
#include <random> 
#include <omp.h>

using namespace std;


int main(){
    // Loop de 100000 iteracoes
    int N = 100000;
    int soma = 0;
    int num_threads = omp_get_max_threads();
    vector<default_random_engine> generators(num_threads);

    for(int j = 0; j < num_threads; j++){
        default_random_engine generator(j);
        generators[j] = generator;

    }
    uniform_real_distribution<double> distribution(0.0, 1.0);
    #pragma omp parallel for reduction(+ : soma)
    for(int i = 0; i < N; i++){

        double x = distribution(generators[omp_get_thread_num()]);
        double y = distribution(generators[omp_get_thread_num()]);

        if(x * x + y * y <= 1){
            soma += 1;
        }

    }

    double pi = (double) 4*soma/N;

    cout << "Pi = " << pi << "\n";


    return 0;
}