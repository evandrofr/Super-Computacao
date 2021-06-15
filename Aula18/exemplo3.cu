#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>

struct is_positive
{
    __host__ __device__
    bool operator()(const double &x)
    {
        return x > 0;
    }
};

struct is_negative
{
    __host__ __device__
    bool operator()(const double &x)
    {
        return x < 0;
    }
};

int main() {
    int N = 2518;
    std::cout << N << "\n";
    thrust::host_vector<double> host(N);
    for(int i = 0; i < N; i++){
        std::cin >> host[i];
    }
    thrust::device_vector<double> stocks(host);
    thrust::device_vector<double> ganho_diario(N - 1);

    thrust::transform(stocks.begin() + 1, stocks.end(), stocks.begin(), ganho_diario.begin(), thrust::minus<double>());

    int Npositive = thrust::count_if(ganho_diario.begin(), ganho_diario.end(), is_positive());

    thrust::replace_if(ganho_diario.begin(), ganho_diario.end(), ganho_diario.begin(), is_negative(), 0.0);

    double positivesSum = thrust::reduce(ganho_diario.begin(), ganho_diario.end(), 0.0, thrust::plus<double>());

    double positivesMean = positivesSum / Npositive;

    std::cout << "quantas vezes o valor subiu? " << Npositive << "\n";
    std::cout << "qual é o aumento médio, considerando só as vezes em que o valor aumentou de fato? " << positivesMean << "\n";


}
