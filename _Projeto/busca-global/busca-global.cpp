#include <iostream>
#include <algorithm>
#include <vector>
#include <random> 

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
    // Pega
    for(int i = 0; i < num_pessoas; i++){
        if(totais[i] < mms){
            mms = totais[i];
        }
    }
    return mms;
}

void busca_global(int num_pessoas, vector<item> itens, vector<item> &melhores_itens, int idx_item, int *melhor_mms, int *total_iter){
    if ((int) itens.size() == idx_item){
        *total_iter += 1;
        // cout << "total_iter: " << *total_iter << "\n";
        int mms = calcula_mms(itens, num_pessoas);
        if(mms > *melhor_mms){
            *melhor_mms = mms;
            // cout << "melhor_mms: " << *melhor_mms << "\n";
            // cout << "mms: " << mms << "\n"; 
            melhores_itens = itens;
        }

    } else {
        for(int x = 0; x < num_pessoas; x++){
            itens[idx_item].dono = x;
            // cout << "Dono: " << itens[idx_item].dono << "\n";
            busca_global(num_pessoas, itens, melhores_itens, idx_item + 1, melhor_mms, total_iter);
        }
    }
}

bool compareValor (item &a, item &b) { return a.valor > b.valor; } // > para decrescente e < para crescente
bool compareIdx   (item &a, item &b) { return a.idx < b.idx; } // > para decrescente e < para crescente

int main(){

    //Pegar variaveis de ambiente
    int seed = 0;
    char *SEED_VAR = getenv("SEED");
    if (SEED_VAR != NULL){
        seed = atoi(SEED_VAR);
    }

    int iter = 100000;
    char *ITER_VAR = getenv("ITER");
    if (ITER_VAR != NULL){
        iter = atoi(ITER_VAR);
    }

    int debug = 0;
    char *DEBUG_VAR = getenv("DEBUG");
    if (DEBUG_VAR != NULL){
        debug = atoi(DEBUG_VAR);
    }

    vector<item> itens;
    vector<item> melhores_itens;
    int melhor_mms = 0;
    int *ptr_melhor_mms = &melhor_mms;
    int total_iter = 0;
    int *ptr_total_iter = &total_iter;

    // Pegando os valores do arquivo
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



    busca_global(pessoas, itens, melhores_itens, 0, ptr_melhor_mms, ptr_total_iter);

    if(debug == 1){
        cerr << total_iter;
    }


    // Print final do MMS mais os index dos itens de cada pessoa
    cout << melhor_mms << "\n";

    for(int x = 0; x < pessoas; x++){
        for(int y = 0; y < size; y++){
            if(melhores_itens[y].dono == x){
                cout << melhores_itens[y].idx << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}