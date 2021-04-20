#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct item{
    int valor;
    int idx;
    int dono;
};


int main(){
    int num_obj;
    int num_pes;
    // cout << "Quantos objetos serão divididos?\n";
    cin >> num_obj;
    // cout << "Para quantas pessoas serão divididos?\n";
    cin >> num_pes;

    vector<vector<int>> matrix_pref;
    for(int i = 0; i < num_pes; i++){
        vector<int> tmp;
        matrix_pref.push_back(tmp);
    }

    for(int i = 0; i < num_pes; i++){
        for(int j = 0; j < num_obj; j++){
            int tmp;
            cin >> tmp;
            matrix_pref[i].push_back(tmp);
        }
    }

    vector<int> MMS_min;
    for(int i = 0; i < num_pes; i++){
        int tmp;
        cin >> tmp;
        MMS_min.push_back(tmp);
    }

    vector<item> itens;
    for(int i = 0; i < num_obj; i++){
        struct item tmp_item;
        tmp_item.idx = i;
        itens.push_back(tmp_item);
    }
    for(int i = 0; i < num_obj; i++){
        int tmp;
        cin >> tmp;
        itens[i].dono = tmp;
        itens[i].valor = matrix_pref[tmp][i];
    }

    vector<int> totais;
    for(int i = 0; i < num_pes; i++){
        totais.push_back(0);
    }
    for(int i = 0; i < num_obj; i++){
        totais[itens[i].dono] += itens[i].valor;
    }
    bool resposta = true;
    for(int i = 0; i < num_pes; i++){
        if(totais[i] < MMS_min[i]){
            resposta = false;
        }
    }

    if (resposta){
        cout << "SIM" << "\n";
    } else {
        cout << "NAO" << "\n";
    }


    return 0;
}