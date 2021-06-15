#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <thrust/functional.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/reduce.h>
#include <thrust/transform.h>

using namespace std;


// struct item{
//     int valor;
//     int idx;
//     int dono;
// };

struct item {
    int valor;
    int idx;
    int dono;

    item(int valor, int idx, int dono): attr(valor, idx, dono) {};

    // TODO: operação customizada aqui
};


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



    // Pegando os valores do arquivo
    int size;
    int pessoas;
    cin >> size;
    cin >> pessoas;

    // Criando vetores
    thrust::host_vector<item> host_itens(size);
    thrust::host_vector<item> host_itens_final(size);
    
    struct item tmp;
    int tmp_valor;
    for(int i = 0; i < size; i++){
        cin >> tmp_valor;
        host_itens[i] = item a(tmp_valor, i, -1);
    }

    thrust::device_vector<item> itens_dev(host_itens);


    // Criando gerador de numeros aleatorios e colocando a seed
    // default_random_engine generator;
    // generator.seed(seed);
    // uniform_int_distribution<int> randomItemPos(0, pessoas-1);
                

    int MMS_final = 0;

    // // Loop de 100000 iteracoes
    // for(int h = 0; h < iter; h++){

    //     for(int i = 0; i < size; i++){
    //         int rand_idx = randomItemPos(generator);
    //         itens[i].dono = rand_idx;
    //     }
        

    //     vector<int> totais;
    //     for (int i = 0; i < size; i++){
    //         totais.push_back(0);         
    //     }

    //     for(int i = 0; i < size; i++){
    //         totais[itens[i].dono] += itens[i].valor;
    //     }


    //     int MMS = 9999999;
    //     int MMS_idx = 999;
    //     for(int i = 0; i < pessoas; i++){
    //         if(totais[i] < MMS){
    //             MMS = totais[i];
    //             MMS_idx = i;
    //         }
    //     }

    //     // ---------------------------------------------------------------------------------
    //     // loop de doacoes
    //     int idx = 0;
    //     while(idx < size){
    //         if((totais[itens[idx].dono] - itens[idx].valor) > MMS){
    //             totais[itens[idx].dono] -= itens[idx].valor;
    //             totais[MMS_idx] += itens[idx].valor;
    //             itens[idx].dono = MMS_idx;


    //             MMS = 9999999;
    //             for(int i = 0; i < pessoas; i++){
    //                 if(totais[i] < MMS){
    //                     MMS = totais[i];
    //                     MMS_idx = i;
    //                 }
    //             }
    //             idx = 0;
    //         } else {
    //             idx++;
    //         }
    //     }
            

    //     // Apenas para a funcao DEBUG
    //     // Printa o MMS de casa iteracao junto com os donos de cada objeto na ordem original

    //     if(debug == 1){
    //         cerr << MMS << " ";

    //         for(int i = 0; i < size; i++){
    //             cerr << itens[i].dono << " ";
    //         }
    //         cerr << "\n";
    //     }
    //     // Caso o MMS da iteracao seja maior que o MMS_final anterior, o substitui
    //     if(MMS > MMS_final){
    //         MMS_final = MMS;
    //         itens_final.clear();
    //         copy(itens.begin(), itens.end(), back_inserter(itens_final));
    //     }
    // }          

    thrust::copy(itens_dev.begin(), itens_dev.end(), host_itens_final.begin());
    // Print final do MMS mais os index dos itens de cada pessoa
    // cout << MMS_final << "\n";

    for(int x = 0; x < pessoas; x++){
        for(int y = 0; y < size; y++){
            if(host_itens_final[y].dono == x){
                cout << host_itens_final[y].idx << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
