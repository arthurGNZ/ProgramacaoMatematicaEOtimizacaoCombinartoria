#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/*
---Problema da mochila---
Entrada: Quantidade de itens n e capacidade W da mochila para cada item i, valor Vi do item e peso Pi do item
Solução viável: Subconjunto de itens com soma de pesos <=w
Função Objetivo: Soma dos valores do subconjunto de itens,
Objetivo: Encontrar uma  solução viável com soma de valores máximo.
*/

//Solução com força bruta: testa todas soluções possíveis e retorna a com o melhor valor
int forca_bruta(int i, int capacidade, int *pesos, int *valores, int n){
    if(i>=n || capacidade==0){
        return 0;
    }
    if(pesos[i]>capacidade){
        return forca_bruta(i+1,capacidade, pesos, valores, n);
    }
    return max((valores[i]+forca_bruta(i+1, capacidade-pesos[i], pesos, valores, n)),(forca_bruta(i+1,capacidade,pesos,valores, n)));
}

//nesta solução, os casos são salvos. Assim, não irá gastar processamento com coisas que já foram
int solucao_2(int i, int capacidade, int *pesos, int *valores, int n, vector<std::vector<int>> &m){
    if(i>=n || capacidade==0){
        return 0;
    }
    if(m[i][capacidade]!=-1){
        return m[i][capacidade];
    }
    if(pesos[i]>capacidade){
        m[i][capacidade]=solucao_2(i+1,capacidade, pesos, valores, n,m);
        return m[i][capacidade];
    }
    m[i][capacidade]=max((valores[i]+solucao_2(i+1, capacidade-pesos[i], pesos, valores, n,m)),(solucao_2(i+1,capacidade,pesos,valores, n,m)));
    return m[i][capacidade];
}
int main() {
    int quant;
    int cap;
    cout << "Digite a quantidade de itens:";
    cin >> quant;
    cout << "Digite a capacidade da mochila:";
    cin >> cap;
    int pesos[quant];
    int valores[quant];
    for(int i=0; i<quant; i++){
        cout << "Digite o valor do item: ";
        cin >> valores[i];
        cout << "Digite o peso do item: ";
        cin >> pesos[i];
    }
    vector<std::vector<int>> m;
    m.resize(quant);
    for(int i=0; i<quant; i++){
        m[i].resize(cap+1,-1);
    }

      
    //cout<<forca_bruta(0,cap,pesos,valores,quant);
    cout<<solucao_2(0,cap,pesos,valores,quant, m);
}
