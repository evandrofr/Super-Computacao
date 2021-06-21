#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/random.h>


struct item{
    int valor;
    int idx;
    int dono;
};

struct raw_access {
    item *itens;
    int *totais;
    int num_pessoas;
    int num_itens;

    __device__
    int operator()(const int &it) {
        // Criando gerador de numeros aleatorios e colocando a seed
        thrust::default_random_engine generator;
        generator.seed(it);
        thrust::uniform_int_distribution<int> randomItemPos(0, num_pessoas-1);

        for(int i = 0; i < num_itens; i++){
            int rand_idx = randomItemPos(generator);
            itens[i+it*num_itens].dono = rand_idx;
            totais[itens[i+it*num_itens].dono + it*num_pessoas] += itens[i+it*num_itens].valor;
        }
        

        int MMS = totais[it*num_pessoas];
        int MMS_idx = 0;
        for(int i = 0; i < num_pessoas; i++){
            if(totais[i+it*num_pessoas] < MMS){
                MMS = totais[i+it*num_pessoas];
                MMS_idx = i;
            }
        }

        // ---------------------------------------------------------------------------------
        // loop de doacoes

        int idx = 0;
        while(idx < num_itens){
            if((totais[itens[idx+it*num_itens].dono + it*num_pessoas] - itens[idx+it*num_itens].valor) > MMS){
                totais[itens[idx+it*num_itens].dono + it*num_pessoas] -= itens[idx+it*num_itens].valor;
                totais[MMS_idx+it*num_pessoas] += itens[idx+it*num_itens].valor;
                itens[idx+it*num_itens].dono = MMS_idx;

                MMS = totais[it*num_pessoas];
                MMS_idx = 0;
                for(int i = 0; i < num_pessoas; i++){
                    if(totais[i+it*num_pessoas] < MMS){
                        MMS = totais[i+it*num_pessoas];
                        MMS_idx = i;
                    }
                }
                idx = 0;
            } else {
                idx++;
            }
        }



        return MMS;
    }
};


struct Filler{

    int num_itens;
    item *itensPequeno;

    __device__
    item operator()(const int &it){
        return itensPequeno[it % num_itens];
    }
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
    int num_itens;
    int num_pessoas;
    std::cin >> num_itens;
    std::cin >> num_pessoas;

    // Criando vetores
    thrust::device_vector<item> itens(num_itens*iter);
    thrust::device_vector<item> itensPequeno(num_itens);
    thrust::device_vector<int>  totais(iter*num_pessoas);
    thrust::device_vector<int>  MMS_result(iter);


    for(int i = 0; i < num_itens; i++){
        int valor;
        std::cin >> valor;
        itensPequeno[i] = {.valor=valor, .idx = i};
    }
    

    Filler filler = {.num_itens = num_itens, .itensPequeno = itensPequeno.data().get()};
    thrust::counting_iterator<int> it2(0);
    thrust::transform(it2, it2+num_itens*iter, itens.begin(), filler);


    thrust::counting_iterator<int> it(0);
    raw_access ra{.itens=itens.data().get(), .totais=totais.data().get(), .num_pessoas=num_pessoas, .num_itens=num_itens};
    thrust::transform(it, it+iter, MMS_result.begin(), ra);

    auto result = thrust::max_element(MMS_result.begin(), MMS_result.end());

    int best_MMS_idx = thrust::distance(MMS_result.begin(), result);


    // Apenas para a funcao DEBUG
    // Printa o MMS de casa iteracao junto com os donos de cada objeto na ordem original

    if (debug == 1) {
        for (int i = 0; i < iter; i++) {
            std::cerr << MMS_result[i] << " ";

            for (int j = 0; j < num_itens; j++){
                item item_ = itens[j+i*num_itens];
                std::cerr << item_.dono << " ";
            }

            std::cerr << "\n";
        }
    }
    // Caso o MMS da iteracao seja maior que o MMS_final anterior, o substitui
          



    // Print final do MMS mais os index dos itens de cada pessoa
    std::cout << MMS_result[best_MMS_idx] << "\n";

    for(int x = 0; x < num_pessoas; x++){
        for(int y = 0; y < num_itens; y++){
            item i_copy = itens[y+num_itens*best_MMS_idx];
            if(i_copy.dono == x){
                std::cout << i_copy.idx << " ";
            }
        }
        std::cout << "\n";
    }


    return 0;
}
