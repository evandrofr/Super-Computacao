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

    vector<vector<item>> resposta;
    for(int i = 0; i < pessoas; i++){
        vector<item> tmp;
        resposta.push_back(tmp);
    }

    int size_vector = size - 1;
    for(int i = 0; i < size; i++){
        uniform_int_distribution<int> randomItemPos(0, size_vector);
        int rand_idx = randomItemPos(generator);
        resposta[i%pessoas].push_back(itens[rand_idx]);
        cout << "rand_idx: " << rand_idx << "\n";
        cout << "Pessoa: " << i%pessoas << "\n";
        cout << "Valor: "<< itens[rand_idx].valor << " IDX: " << itens[rand_idx].idx << "\n";
        cout << "-------------------------------------------------\n";
        

        itens.erase(itens.begin() + rand_idx);
        size_vector -= 1;
    }

    vector<int> lens;
    for(int i = 0; i < pessoas; i++){
        int len = resposta[i].size();
        lens.push_back(len);
    }

    int MMS = 9999999;
    int MMS_idx = 999;
    vector<int> totais;
    for(int i = 0; i < pessoas; i++){
        int total = 0;
        for(int j = 0; j < lens[i]; j++){
            total += resposta[i][j].valor;
        }
        totais.push_back(total);
        if (total < MMS){
            MMS = total;
            MMS_idx = i;
        }
    }
    cout << "MMS: " << MMS << "\n";
    cout << "MMS_idx: " << MMS_idx << "\n";

    // for(int i = 0; i < pessoas; i++){
    //     int valor_total = totais[i];
    //     for(int j = 0; j < lens[i]; j++){
    //         if(valor_total - )
    //     }
    // }

    
    for(int i = 0; i < pessoas; i++){
        for(int j = 0; j < lens[i]; j++){
            cout << resposta[i][j].idx << " ";
        }
        cout << "\n";
    }

    return 0;
}