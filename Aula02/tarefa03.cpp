#include<iostream>
#include<math.h>
#include <iomanip>

using namespace std;

int main(){
    int n;
    float S = 0;
    cout << "Digite um número inteiro: ";
    cin >> n;

    for(int i=0; i <= n; i++){
        S = S + pow(0.5, i);
    }
    cout << "Resultado: " << setprecision(15) << S << "\n";
    return 0;
}