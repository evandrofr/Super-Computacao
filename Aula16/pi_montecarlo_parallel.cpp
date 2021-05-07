#include <iostream>
#include <algorithm>
#include <random> 

using namespace std;


int main(){

    int seed = 0;

    // Criando gerador de numeros aleatorios e colocando a seed
    default_random_engine generator;
    generator.seed(seed);  
    uniform_real_distribution<double> distribution(0.0, 1.0);

    // Loop de 100000 iteracoes
    int N = 100000;
    int soma = 0;
    #pragma omp parallel for reduction(+ : soma)
    for(int i = 0; i < N; i++){
        double x,y;
        #pragma omp critical
        {
            x = distribution(generator);
            y = distribution(generator);
        }

        if((x*x + y*y) <= 1){
            soma += 1;
        }

    }

    double pi = (double) 4*soma/N;

    cout << "Pi = " << pi << "\n";


    return 0;
}