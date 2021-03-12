#include <iostream>
#include <algorithm>
#include <vector>
#include <random> 

using namespace std;

struct item{
    int peso;
    int valor;
    int idx;
};


bool comparePeso  (item &a, item &b) { return a.peso  > b.peso; }
bool compareValor (item &a, item &b) { return a.valor < b.valor; }

int main(){
    vector<item> itens;
    vector<int> resposta;

    int pesoTotal = 0;
    int valorTotal = 0;
    int numeroItens = 0;

    // Gerador de números pseudo aleatórios
    double rand;
    seed_seq seed{10};
    default_random_engine generator{seed};
    uniform_real_distribution<double> distribution(0.0, 2.0);


    int size;
    int maxPeso;
    cout << "Quantos pontos terão a matriz?\n";
    cin >> size;
    cout << "Qual o peso máximo da mochila?\n";
    cin >> maxPeso;

    struct item tmp;
    for(int i = 0; i < size; i++){
        cout << "(" << i + 1 << "/" << size << ")\n";
        cout << "Entre com o peso: \n";
        cin >> tmp.peso;
        cout << "Entre com o valor: \n";
        cin >> tmp.valor;
        tmp.idx = i;
        itens.push_back(tmp);
    }

    sort(itens.begin(), itens.end(), comparePeso);
    // sort(itens.begin(), itens.end(), compareValor);


    cout << "----------------------------------------------\n";

    for(int i = 0; i < size; i++){
        rand = distribution(generator); // gera número pseudo aleatório
        if (rand > 1){
            if(pesoTotal + itens[i].peso < maxPeso){
                resposta.push_back(itens[i].idx);
                pesoTotal += itens[i].peso;
                valorTotal += itens[i].valor;
                numeroItens++;
            }

        }

    }

    for(int i = 0; i < numeroItens; i++){
        cout << resposta[i] << " ";
    }
    cout << "\n";

    return 0;
}