#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct item{
    int valor;
    int idx;
};


bool compareValor (item &a, item &b) { return a.valor > b.valor; } // > para decrescente e < para crescente
bool compareIdx   (item &a, item &b) { return a.idx < b.idx; } // > para decrescente e < para crescente

int main(){
    vector<item> itens;


    int size;
    int pessoas;
    // cout << "Quantos objetos para dividir?\n";
    cin >> size;
    // cout << "Quantas pessoas para dividir?\n";
    cin >> pessoas;

    struct item tmp;
    for(int i = 0; i < size; i++){
        // cout << "(" << i + 1 << "/" << size << ")\n";
        // cout << "Entre com o valor: \n";
        cin >> tmp.valor;
        tmp.idx = i;
        itens.push_back(tmp);
    }

    sort(itens.begin(), itens.end(), compareValor);


    // cout << "----------------------------------------------\n";
    // for(int i = 0; i < size; i++){
    //     cout << itens[i].idx << " ";
    // }
    // cout << "\n";

    vector<vector<item>> resposta;
    for(int i = 0; i < pessoas; i++){
        vector<item> tmp;
        resposta.push_back(tmp);
    }

    for(int i = 0; i < size; i++){
        int index = i%pessoas;
        resposta[index].push_back(itens[i]);
    }

    vector<int> lens;
    for(int i = 0; i < pessoas; i++){
        int len = resposta[i].size();
        lens.push_back(len);
    }
    int minimo = 999999;
    // int idx_minimo = 0;
    for(int i = 0; i < pessoas; i++){
        int total_parcial = 0;
        for(int j = 0; j < lens[i]; j++){
            total_parcial += resposta[i][j].valor;
        }
        if (total_parcial < minimo){
            minimo = total_parcial;
            // idx_minimo = i;
        }
    }

    for(int i = 0; i < pessoas; i++){
        sort(resposta[i].begin(), resposta[i].end(), compareIdx);
    }

    cout << minimo << "\n";
    
    for(int i = 0; i < pessoas; i++){
        for(int j = 0; j < lens[i]; j++){
            cout << resposta[i][j].idx << " ";
        }
        cout << "\n";
    }
    
    return 0;
}