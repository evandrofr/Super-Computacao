#include <iostream>
#include <algorithm>
#include <random> 

using namespace std;


int main(){
    // Loop de 100000 iteracoes
    int N = 100000;
    int soma = 0;
    #pragma omp parallel for reduction(+ : soma)
    for(int i = 0; i < N; i++){

        default_random_engine generator(i);
        uniform_real_distribution<double> distribution(0.0, 1.0);

        double x = distribution(generator);
        double y = distribution(generator);

        if(x * x + y * y <= 1){
            soma += 1;
        }

    }

    double pi = (double) 4*soma/N;

    cout << "Pi = " << pi << "\n";


    return 0;
}