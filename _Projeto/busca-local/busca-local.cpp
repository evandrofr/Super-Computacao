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
    // Criando vetores
    vector<item> itens;
    vector<vector<item>> resposta;
    vector<vector<item>> resposta_final;
    vector<int> lens;
    vector<int> lens_final;
    vector<int> totais;

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

    // Criando gerador de numeros aleatorios e colocando a seed
    default_random_engine generator;
    generator.seed(seed);  

    // Loop de 100000 iteracoes
    int MMS_final = 0;
    for(int h = 0; h < iter; h++){
        // Copiando vetor itens para poder altera-lo
         vector<item> itens_copy(itens.size());
         copy(itens.begin(), itens.end(), itens_copy.begin());
        
        // Limpando vetor resposta e preenchendo com um vetor vazio para cada pessoa
        resposta.clear();
        for(int i = 0; i < pessoas; i++){
            vector<item> tmp;
            resposta.push_back(tmp);
        }

        // Distribuindo itens para as pessoas de forma aleatoria
        // Sorteia um numero correspondendo ao index do item, atribui um dono ao item sorteaod, coloca esse item na lista resposta
        // Apaga o item e diminui o numero do proximo sorteio
        int size_vector = size - 1;
        for(int i = 0; i < size; i++){
            uniform_int_distribution<int> randomItemPos(0, size_vector);
            int rand_idx = randomItemPos(generator);
            itens_copy[rand_idx].dono = i%pessoas;
            resposta[i%pessoas].push_back(itens_copy[rand_idx]);

            itens_copy.erase(itens_copy.begin() + rand_idx);
            size_vector -= 1;
        }
        
        // Limpa o vetor de tamanho e o preenche com o tamanho dos vetores de cada pessoa
        lens.clear();
        for(int i = 0; i < pessoas; i++){
            int len = resposta[i].size();
            lens.push_back(len);
        }

        // Calcula o MMS e salva o idx da pessoa que e MMS
        // Tambem limpa o vetor de totais e o preenche com o valor total de cada pessoa
        int MMS = 9999999;
        int MMS_idx = 999;
        totais.clear();
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

        // ---------------------------------------------------------------------------------
        // loop de doacoes
        bool loop = true;
        while(loop){
            // Percorre cada item de cada pessoa e verifica se o valor total dessa pessoa sem esse objeto e maior que o MMS
            // Caso seja ocorre a doacao
            // Passa o item para o MMS e quebra o loop
            bool break_bool = false;
            for(int i = 0; i < pessoas; i++){
                int valor_total = totais[i];
                for(int j = 0; j < lens[i]; j++){
                    if(valor_total - resposta[i][j].valor > MMS){
                        struct item tmp;
                        tmp = resposta[i][j];
                        tmp.dono = MMS_idx;
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
            
            // Limpa o vetor de tamanho e o preenche com o tamanho dos vetores de cada pessoa
            lens.clear();
            for(int a = 0; a < pessoas; a++){
                int len = resposta[a].size();
                lens.push_back(len);
            }


            // Calcula o MMS e salva o idx da pessoa que e MMS
            // Tambem limpa o vetor de totais e o preenche com o valor total de cada pessoa
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
        }
        // Ordena os vetores de cada pessoa pelos index dos itens
        for(int i = 0; i < pessoas; i++){
            sort(resposta[i].begin(), resposta[i].end(), compareIdx);
        }

        // Apenas para a funcao DEBUG
        // Printa o MMS de casa iteracao junto com os donos de cada objeto na ordem original
        if(debug == 1){
            cerr << MMS << " ";

            for(int r = 0; r < (int) itens.size(); r++){
                for(int x = 0; x < pessoas; x++){
                    for(int y = 0; y < lens[x]; y++){
                        if(itens[r].idx == resposta[x][y].idx){
                            cerr << resposta[x][y].dono << " ";
                        }
                    }
                }
            }
            cerr << "\n";
        }
        // Caso o MMS da iteracao seja maior que o MMS_final anterior, o substitui
        if(MMS > MMS_final){
            MMS_final = MMS;
            lens_final = lens;
            resposta_final = resposta;
        }
    }
    // Print final do MMS mais os index dos itens de cada pessoa
    cout << MMS_final << "\n";

    for(int x = 0; x < pessoas; x++){
        for(int y = 0; y < lens_final[x]; y++){
            cout << resposta_final[x][y].idx << " ";
        }
        cout << "\n";
    }

    return 0;
}