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
    for(int i = 0; i < N; i++){
        double x = distribution(generator);
        double y = distribution(generator);

        double circulo = x*x + y*y;
        if(circulo <= 1){
            soma += 1;
        }

    }

    double pi = (double) 4*soma/N;

    cout << "Pi = " << pi << "\n";


    return 0;
}