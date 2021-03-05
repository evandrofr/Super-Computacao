#include<iostream>
#include<math.h>
#include <iomanip>
#include<vector>

using namespace std;

void calcula_distancias(vector<vector<double>> &matrix_dist, vector<double> x, vector<double> y, int numero_pontos){
    cout << "Entrei\n";
    for(int i = 0; i < numero_pontos; i++){
        vector<double> tmp;
        matrix_dist.push_back(tmp);
        for(int i2 = 0; i2 < numero_pontos; i2++){
            if(i <= i2){
                double dx = (x[i] - x[i2]);
                double dy = (y[i] - y[i2]);
                double dist = sqrt(dx*dx+dy*dy);
                matrix_dist[i].push_back(dist);  
            } else {
                matrix_dist[i].push_back(matrix_dist[i2][i]);
            }
        }
    }

}

int main(){
    int sizeI;
    cout << "Quantos pontos terão a matriz?\n";
    cin >> sizeI;

    vector<double> x;
    vector<double> y;

    double tmpX, tmpY;
    for(int i = 0; i < sizeI; i++){
        cout << "Ponto " << "(" << i+1 << "/" << sizeI << ")\n";
        cout << "Entre com X: \n";
        cin >> tmpX;
        cout << "Entre com Y: \n";
        cin >> tmpY;
        x.push_back(tmpX);
        y.push_back(tmpY);
    }

    vector<vector<double>> matrix_dist;
    calcula_distancias(matrix_dist, x, y, sizeI);
    
    for (int i = 0; i < sizeI; i++){
        for (int j = 0; j < sizeI; j++){
            cout << fixed;
            cout << setprecision(2) << matrix_dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}