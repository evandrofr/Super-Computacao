#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct item{
    int peso;
    int valor;
    int idx;
};

bool compare(item &a, item &b) { return a.peso > b.peso; }

int main(){
    vector<item> itens;
    vector<int> resposta;

    int pesoTotal = 0;
    int valorTotal = 0;
    int numeroItens = 0;


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
    cout << itens[0].valor << "\n";

    sort(itens.begin(), itens.end(), compare);


    cout << "----------------------------------------------\n";
    // for(int i = 0; i < size; i++){
    //     cout << itens[i].valor << "\n";
    // }
    // cout << "----------------------------------------------\n";

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

    return 0;
}