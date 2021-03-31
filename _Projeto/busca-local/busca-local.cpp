#include <iostream>
#include <algorithm>
#include <vector>
#include <random> 

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
    cin >> size;
    cin >> pessoas;

    struct item tmp;
    for(int i = 0; i < size; i++){
        cin >> tmp.valor;
        tmp.idx = i;
        itens.push_back(tmp);
    }

    // sort(itens.begin(), itens.end(), compareValor);
    default_random_engine generator;
    generator.seed(0);
    uniform_int_distribution<int> distribution(0, size-1);

    

    vector<vector<item>> resposta;
    for(int i = 0; i < pessoas; i++){
        vector<item> tmp;
        resposta.push_back(tmp);
    }

    int MMS = 999999;
    int MMS_idx = 999;
    int size_copy = size;
    for(int i = 0; i < size; i++){
        int rand_idx = distribution(generator);
        cout << "rand_idx original: " << rand_idx << "\n";
        rand_idx = rand_idx%(size_copy);
        cout << "rand_idx resto: "<< rand_idx << "\n";
        cout << "size_copy: " << size_copy << "\n";
        cout << "Valor: "<< itens[rand_idx].valor << " IDX: " << itens[rand_idx].idx << "\n";
        cout << "-------------------------------------------------\n";
        itens.erase(itens.begin() + rand_idx);
        resposta[i].push_back(itens[rand_idx]);
        if(itens[rand_idx].valor < MMS){
            MMS = itens[rand_idx].valor;
            MMS_idx = i;
        }
        size_copy -= 1;
    }
    // cout << "MMS: " << MMS << "\n";
    // cout << "MMS_idx: " << MMS_idx << "\n";

    vector<int> lens;
    for(int i = 0; i < pessoas; i++){
        int len = resposta[i].size();
        lens.push_back(len);
    }


    // for(int i = 0; i < pessoas; i++){
    //     int total = 0;
    //     for(int j = 0; j < lens[i]; j++){
    //         total += resposta[i][j]
    //     }
    //     if (total < MMS)
    // }


    
    for(int i = 0; i < pessoas; i++){
        for(int j = 0; j < lens[i]; j++){
            cout << resposta[i][j].idx << " ";
        }
        cout << "\n";
    }

    return 0;
}