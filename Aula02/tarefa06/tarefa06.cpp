#include<iostream>
#include<math.h>
#include <iomanip>
#include<vector>

using namespace std;

int main(){
    vector<vector<double>> matrix;
    int sizeI;
    cout << "Quantos pontos terão a matriz?\n";
    cin >> sizeI;

    double tmpX, tmpY;
    for(int i = 0; i < sizeI; i++){
        cout << "Ponto " << "(" << i+1 << "/" << sizeI << ")\n";
        cout << "Entre com X: \n";
        cin >> tmpX;
        cout << "Entre com Y: \n";
        cin >> tmpY;
        matrix.push_back({tmpX,tmpY});
    }
    double dx;
    double dy;
    double dist;

    for(int i = 0; i < sizeI; i++){
        for(int i2 = 0; i2 < sizeI; i2++){
            if(i != i2){
                dx = (matrix[i][0] - matrix[i2][0])*(matrix[i][0] - matrix[i2][0]);
                dy = (matrix[i][1] - matrix[i2][1])*(matrix[i][1] - matrix[i2][1]);
                dist = sqrt(dx+dy);
                cout << "Dist ponto " << i+1 << " a " << i2+1 << ": " << dist << "\n";
            }
        }
    }
    return 0;
}