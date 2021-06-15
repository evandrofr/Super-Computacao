#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/random/linear_congruential_engine.h>
#include <thrust/random/uniform_real_distribution.h>
#include <iostream>

// nvcc -std=c++14 -O3 tarefa1.cu -o t1 && ./t1

int main()
{
    int seed;
    std::cin >> seed;
    thrust::minstd_rand rng(seed);

    thrust::uniform_real_distribution<double> dist(25, 40);

    for (int i = 0; i < 10; i++)
        std::cout << dist(rng) << " ";
    std::cout << "\n";
}