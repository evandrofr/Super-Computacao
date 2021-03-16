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


int main(){
    vector<item> itens;

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

    cout << "----------------------------------------------\n";
    default_random_engine generator;
    generator.seed(10);
    for(int j = 0; j < 10; j++){
        vector<int> resposta;
        // Gerador de números pseudo aleatórios
        uniform_real_distribution<double> distribution(0.0, 1.0);

        double rand;
        int pesoTotal = 0;
        int valorTotal = 0;
        int numeroItens = 0;


        for(int i = 0; i < size; i++){
            rand = distribution(generator); // gera número pseudo aleatório
            if(rand > 0.5){
                if(pesoTotal + itens[i].peso < maxPeso){
                    resposta.push_back(itens[i].idx);
                    pesoTotal += itens[i].peso;
                    valorTotal += itens[i].valor;
                    numeroItens++;
                }
            } 
        }

        for(int i = 0; i < size; i++){
            if(pesoTotal + itens[i].peso < maxPeso){
                resposta.push_back(itens[i].idx);
                pesoTotal += itens[i].peso;
                valorTotal += itens[i].valor;
                numeroItens++;
            }

        }


        for(int i = 0; i < numeroItens; i++){
            cout << resposta[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}