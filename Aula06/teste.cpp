#include <iostream>
#include <algorithm>
#include <vector>
#include <random> 

using namespace std;

int main(){
    double rand;
    seed_seq seed{10};
    default_random_engine generator{seed};
    uniform_real_distribution<double> distribution(0.0, 4.0);
    uniform_int_distribution<int> distribution2(0, 4000);
    for (int i = 0; i < 10; i++){
        rand = distribution(generator); // gera número
        cout << rand << "\n";
    }
    for (int i = 0; i < 10; i++){
        rand = distribution2(generator); // gera número
        cout << rand << "\n";
    }

    return 0;
}