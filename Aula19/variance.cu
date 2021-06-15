#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>

struct variance{
    int N;
    double mean;

    variance(int n, double m): N(n), mean(m) {};
    __host__ __device__
    double operator()(const double &x){
        double v = (x - mean) * (x - mean)/N;
        return v;
    }
    
};

int main() {
    int N = 0;

    thrust::host_vector<double> hostApple;
    thrust::host_vector<double> hostMicrosoft;

    while (std::cin.fail() == false) {
        N += 1;

        double aapl, msft;

        std::cin >> aapl >> msft;
        hostApple.push_back(aapl);
        hostMicrosoft.push_back(msft);
    }

    thrust::device_vector<double> AAPL(hostApple);
    thrust::device_vector<double> MSFT(hostMicrosoft);
    thrust::device_vector<double> diff(N);

    thrust::transform(AAPL.begin(), AAPL.end(), MSFT.begin(), diff.begin(), thrust::minus<double>());

    double mean = thrust::reduce(diff.begin(), diff.end(), 0.0, thrust::plus<double>())/N;
    std::cout << "Media: " << mean << "\n";

    thrust::device_vector<double> vetorV(N);
    thrust::transform(diff.begin(), diff.end(), vetorV.begin(), variance(N,mean));

    double variancia = thrust::reduce(vetorV.begin(), vetorV.end(),0.0,thrust::plus<double>());
    std::cout << "Variancia: " << variancia << "\n";

}

