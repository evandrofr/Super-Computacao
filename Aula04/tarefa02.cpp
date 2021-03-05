#include<iostream>
#include<math.h>
#include <iomanip>
#include<vector>

using namespace std;

void calcula_distancias(vector<double> &matrix_dist, vector<double> x, vector<double> y, int numero_pontos){
    cout << "Entrei\n";
    for(int i = 0; i < numero_pontos; i++){
        for(int j = 0; j < numero_pontos; j++){
            double dx = (x[i] - x[j]);
            double dy = (y[i] - y[j]);
            double dist = sqrt(dx*dx+dy*dy);
            matrix_dist[i*numero_pontos + j] = dist;  
        }
    }

}

int main(){
    int size;
    cout << "Quantos pontos terão a matriz?\n";
    cin >> size;

    vector<double> x;
    vector<double> y;
    x.reserve(size);
    y.reserve(size);

    vector<double> matrix_dist;
    matrix_dist.resize(size * size);

    double tmpX, tmpY;
    for(int i = 0; i < size; i++){
        cout << "Ponto " << "(" << i+1 << "/" << size << ")\n";
        cout << "Entre com X: \n";
        cin >> tmpX;
        cout << "Entre com Y: \n";
        cin >> tmpY;
        x.push_back(tmpX);
        y.push_back(tmpY);
    }

    
    calcula_distancias(matrix_dist, x, y, size);
    
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout << fixed;
            cout << setprecision(2) << matrix_dist[i*size + j] << " ";
        }
        cout << "\n";
    }

    return 0;
}