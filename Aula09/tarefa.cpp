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


int busca_exaustiva(int size, vector<item> itens, int carga_total, int i, vector<int> &usados, vector<int> %melhor){
    if(size == i) return 0;
    int comI;
    int semI = busca_exaustiva(size, itens, carga_total, i+1);
    if(carga_total - itens[i].peso >= 0){
        comI = busca_exaustiva(size, itens, carga_total - itens[i].peso, i+1) + itens[i].valor;
    } else {
        comI = semI;
    }

    return max(comI, semI);
}


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

    cout << "-----------------------------------------------------------------\n";

    int valor_mochila;
    valor_mochila = busca_exaustiva(size, itens, maxPeso, 0);

    cout << valor_mochila << "\n";

    return 0;
}