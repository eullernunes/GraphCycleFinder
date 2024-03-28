#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <set>


using namespace std;

class Grafo
{
    private:
        int V;					 // número de vértices
	    vector<vector<int>> adj; // lista de adjacência
	    set<vector<int>> ciclos; // ciclos únicos

        void dfs(int v, vector<bool> &visitado, vector<int> &caminho, int antecessor);
        bool ehCicloValido(const vector<int> &ciclo);

    public:
        Grafo(int v);
        void addAresta(int v, int w);
        void encontrarCiclosDfs();
        void encontrarCiclosPorPermutacao();
};

#endif