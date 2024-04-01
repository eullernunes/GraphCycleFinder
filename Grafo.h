#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <set>

using namespace std;

class Grafo {
private:
    int V;                        // Número de vértices
    vector<vector<int>> adj;      // Lista de adjacência
    set<vector<int>> ciclos;      // Ciclos únicos
    bool imprimirCiclos = true;
    bool imprimirPermutacoes = true;

    void dfs(int v, vector<bool> &visitado, vector<int> &caminho, int antecessor);
    bool ehCicloValido(const vector<int> &ciclo);
    void permutarEVerificarCiclos(vector<int> &vertices, int inicio, set<vector<int>> &ciclosPermutacao, bool imprimirPermutacoes);

public:
    Grafo(int V);
    void addAresta(int v, int w);
    void encontrarCiclosDfs();
    void encontrarCiclosPorPermutacao();
};

#endif
