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

    
    default_random_engine generator;
    generator.seed(seed);  

    int MMS_final = 0;
    vector<vector<item>> resposta_final;
    vector<int> lens;

    for(int h = 0; h < iter; h++){
        // cout << "h: " << h << "\n";
         vector<item> itens_copy(itens.size());
         copy(itens.begin(), itens.end(), itens_copy.begin());
        

        vector<vector<item>> resposta;
        for(int i = 0; i < pessoas; i++){
            vector<item> tmp;
            resposta.push_back(tmp);
        }

        int size_vector = size - 1;
        for(int i = 0; i < size; i++){
            uniform_int_distribution<int> randomItemPos(0, size_vector);
            int rand_idx = randomItemPos(generator);
            resposta[i%pessoas].push_back(itens_copy[rand_idx]);
            // cout << "rand_idx: " << rand_idx << "\n";
            // cout << "Pessoa: " << i%pessoas << "\n";
            // cout << "Valor: "<< itens[rand_idx].valor << " IDX: " << itens[rand_idx].idx << "\n";
            // cout << "-------------------------------------------------\n";
            

            itens_copy.erase(itens_copy.begin() + rand_idx);
            size_vector -= 1;
        }

        lens.clear();
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
        // cout << "MMS: " << MMS << "\n";
        // cout << "MMS_idx: " << MMS_idx << "\n";
        // ---------------------------------------------------------------------------------
        
        bool loop = true;
        while(loop){
            bool break_bool = false;
            for(int i = 0; i < pessoas; i++){
                int valor_total = totais[i];
                for(int j = 0; j < lens[i]; j++){
                    if(valor_total - resposta[i][j].valor > MMS && MMS_idx != i){
                        // cout << "-----------------------------------------------\n";
                        item tmp = resposta[i][j];
                        // cout << "De: " << "i = " << i << " j = " << j << " De valor: " << tmp.valor << " De idx: " << tmp.idx <<" | Para: " << "i = " << MMS_idx << "\n";
                        resposta[MMS_idx].push_back(tmp);
                        resposta[i].erase(resposta[i].begin() + j);
                        break_bool = true;
                        break;
                    }
                }
                if(break_bool){
                    break;
                } else if (i == pessoas - 1){
                    loop = false;
                }
            }
            

            lens.clear();
            for(int a = 0; a < pessoas; a++){
                int len = resposta[a].size();
                lens.push_back(len);
            }


            totais.clear();
            MMS = 999999;
            for(int b = 0; b < pessoas; b++){
                int total = 0;
                for(int c = 0; c < lens[b]; c++){
                    total += resposta[b][c].valor;
                }

                totais.push_back(total);
                if (total < MMS){
                    MMS = total;
                    MMS_idx = b;
                }
            }
            // cout << "MMS: " << MMS << "\n";
            // cout << "MMS_idx: " << MMS_idx << "\n";
        }

        for(int i = 0; i < pessoas; i++){
            sort(resposta[i].begin(), resposta[i].end(), compareIdx);
        }

        if(MMS > MMS_final){
            MMS_final = MMS;
            resposta_final.clear();
            for(int p = 0; p < pessoas; p++){
                resposta_final.push_back(resposta[p]);
            }

        }
    }
        cout << MMS_final << "\n";

        for(int x = 0; x < pessoas; x++){
            for(int y = 0; y < lens[x]; y++){
                cout << resposta_final[x][y].idx << " ";
            }
            cout << "\n";
        }

    return 0;
}