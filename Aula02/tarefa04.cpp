#include<iostream>
#include<math.h>
#include <iomanip>

using namespace std;

int main(){
    int n;
    float mi = 0;
    float sigma2 = 0;
    cout << "Digite um número inteiro: ";
    cin >> n;
    float *values = new float[n];

    for(int i=0; i < n; i++){
        cout << "(" << i+1 << "/" << n << ") " << "Digite um número fracionário: \n";
        cin >> values[i];
    }

    for(int i=0; i < n; i++){
        mi += values[i];
    }
    mi = mi/n;

    for(int i=0; i < n; i++){
        sigma2 += pow(values[i] - mi, 2); 
    }
    sigma2 = sigma2/n;

    cout << "Media: " << setprecision(10) << mi << "\n";
    cout << "Variancia: " << setprecision(10) << sigma2 << "\n";
    return 0;
}