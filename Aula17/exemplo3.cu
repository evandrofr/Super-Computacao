#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>

int main() {
    int N = 2518;
    thrust::host_vector<double> host(N);
    double tmp;
    for(int i = 0; i < N; i++){
        std::cin >> tmp;
        host[i] = tmp;
    }
    /* na linha abaixo os dados são copiados
       para GPU */
    auto start_time = std::chrono::high_resolution_clock::now();
    thrust::device_vector<double> dev(host);    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cerr << "Alocação e cópia para GPU: " << runtime.count() << "ms\n";


    double mediaAnual = thrust::reduce(dev.end() -365, dev.end(), 0.0, thrust::plus<double>()) /N;
    std::cout << "Media Anual: " << mediaAnual << "\n";



}
