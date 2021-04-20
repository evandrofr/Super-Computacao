#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct item{
    int valor;
    int idx;
    int dono;
};

int calcula_mms(vector<item> itens, int num_pessoas){
    vector<int> totais;
    for(int i = 0; i < num_pessoas; i++){
        totais.push_back(0);
    }
    for(int i = 0; i < (int) itens.size(); i++){
        totais[itens[i].dono] += itens[i].valor;
    }
    int mms = 0;
    // Calculando a soma de todos os itens para ser o valor maximo possivel
    for(int i = 0; i < (int) itens.size(); i++){
        mms += itens[i].valor;
    }
    // Pega o menor dos valores de totais
    for(int i = 0; i < num_pessoas; i++){
        if(totais[i] < mms){
            mms = totais[i];
        }
    }
    return mms;
}


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

    vector<item> itens;
    for(int i = 0; i < num_obj; i++){
        struct item tmp_item;
        tmp_item.idx = i;
        tmp_item.dono = num_pes;
        itens.push_back(tmp_item);
    }

    bool acabou = false;
    int idx = 0;
    while (!acabou) {
        int pref_max = 0;
        int pref_max_idx = 0;
        for(int j = 0; j < num_obj; j ++){
            if(matrix_pref[idx%num_pes][j] > pref_max){
                if(itens[j].dono == num_pes){
                    pref_max = matrix_pref[idx%num_pes][j];
                    pref_max_idx = j;
                }
            }
        }
        itens[pref_max_idx].valor = pref_max;
        itens[pref_max_idx].dono = idx%num_pes;

        if(idx == num_obj - 1){
            acabou = true;
        }

        idx += 1;
    }

    int MMS = calcula_mms(itens, num_pes);

    cout << MMS << "\n";
    for(int x = 0; x < num_pes; x++){
        for(int y = 0; y < num_obj; y++){
            if(itens[y].dono == x){
                cout << itens[y].idx << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}