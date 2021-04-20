#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct frete{
    float preco;
    float distancia;
    int idx_preco;
    int idx_dist;
};

struct fretista{
    float preco;
    int idx;
};

struct distancia{
    float distancia;
    int idx;
};

bool comparaPreco (fretista &a, fretista &b) { return a.preco > b.preco; } // > para decrescente e < para crescente
bool comparaDistancia (distancia &a, distancia &b) { return a.distancia < b.distancia; } // > para decrescente e < para crescente
bool comparaIdx (frete &a, frete &b) { return a.idx_dist < b.idx_dist; } // > para decrescente e < para crescente

int main(){
    vector<frete> fretes;
    vector<fretista> precos;
    vector<distancia> distancias;
    int size;
    // cout << "Quantos fretes serão realizados?\n";
    cin >> size;

    struct distancia tmp_dist;
    for(int i = 0; i < size; i++){
        // cout << "(" << i + 1 << "/" << size << ")\n";
        // cout << "Entre com o valor(dist): \n";
        cin >> tmp_dist.distancia;
        tmp_dist.idx = i;
        distancias.push_back(tmp_dist);
    }

    struct fretista tmp_preco;
    for(int i = 0; i < size; i++){
        // cout << "(" << i + 1 << "/" << size << ")\n";
        // cout << "Entre com o valor(preco): \n";
        cin >> tmp_preco.preco;
        tmp_preco.idx = i;
        precos.push_back(tmp_preco);
    }
    sort(precos.begin(), precos.end(), comparaPreco);
    sort(distancias.begin(), distancias.end(), comparaDistancia);

    float menor_custo = 0;
    struct frete tmp_frete;
    for(int i = 0; i < size; i++){
        tmp_frete.preco = precos[i].preco;
        tmp_frete.distancia = distancias[i].distancia;
        tmp_frete.idx_preco = precos[i].idx;
        tmp_frete.idx_dist = distancias[i].idx;
        menor_custo += tmp_frete.preco*tmp_frete.distancia;
        fretes.push_back(tmp_frete);
    }

    sort(fretes.begin(), fretes.end(), comparaIdx);

    // cout << "----------------------------------------------\n";
    cout << menor_custo << "\n";
    for(int i = 0; i < size; i++){
        cout << fretes[i].idx_preco << "\n";
    }

    //  for(int i = 0; i < size; i++){
    //     cout << precos[i].idx << "\n";
    // }

    return 0;
}