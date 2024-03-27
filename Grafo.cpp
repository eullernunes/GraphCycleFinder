#include "Grafo.h"

#include <algorithm>
#include <numeric>
#include <iostream>

Grafo::Grafo(int V)
{
	this->V = V;
	adj.resize(V);
}

void Grafo::addAresta(int v, int w)
{
	adj[v].push_back(w); // adiciona w à lista de v
	adj[w].push_back(v); // adiciona v à lista de w
}

void Grafo::dfs(int v, vector<bool> &visitado, vector<int> &caminho, int antecessor)
{
    visitado[v] = true;
    caminho.push_back(v);
    
    for (int u : adj[v])
    {
        if (!visitado[u])
        {
            dfs(u, visitado, caminho, v);
        }
        else if (u != antecessor && find(caminho.begin(), caminho.end(), u) != caminho.end())
        {
            // Encontrou um ciclo
            auto start = find(caminho.begin(), caminho.end(), u);
            vector<int> ciclo(start, caminho.end());

            if (ciclo.size() > 2)
            {
                sort(ciclo.begin(), ciclo.end());
                ciclos.insert(ciclo);
            }
        }
    }

    caminho.pop_back();
}


bool Grafo::ehCicloValido(const vector<int> &ciclo)
{
	if (ciclo.front() != ciclo.back() || ciclo.size() < 3)
		return false; // verifica se é um ciclo e tem tamanho mínimo

	for (size_t i = 0; i < ciclo.size() - 1; ++i)
	{
		// verifica se cada aresta do ciclo existe
		if (find(adj[ciclo[i]].begin(), adj[ciclo[i]].end(), ciclo[i + 1]) == adj[ciclo[i]].end())
		{
			return false;
		}
	}
	return true;
}

void Grafo::encontrarCiclosDfs()
{
	vector<bool> visitado(V, false);
	vector<int> caminho;

	for (int i = 0; i < V; i++)
	{
	//cout << "oi teste" << endl;
		if (!visitado[i])
		{
			dfs(i, visitado, caminho, -1);
		}
	}

	// imprime os ciclos encontrados


	for (const auto &ciclo : ciclos)
	{
		vector<int> cicloImprimivel = ciclo;
		cicloImprimivel.push_back(ciclo.front());
		for (int v : cicloImprimivel)
		{
			cout << v << " ";
		}
		cout << endl;
	}

}

void Grafo::encontrarCiclosPorPermutacao()
{
	set<vector<int>> ciclosPermutacao;
	vector<int> vertices(V);
	iota(vertices.begin(), vertices.end(), 0);
	// gera permutações e verifica ciclos
	do
	{
		for (int len = 3; len <= V; ++len)
		{
			vector<int> ciclo(vertices.begin(), vertices.begin() + len);
			ciclo.push_back(ciclo.front());
			if (ehCicloValido(ciclo))
			{
				cout << V << " ";
				ciclo.pop_back();
				sort(ciclo.begin(), ciclo.end());
				ciclo.push_back(ciclo.front());
				ciclosPermutacao.insert(ciclo);
			}
		}
	} while (next_permutation(vertices.begin(), vertices.end()));

	// imprime os ciclos únicos encontrados por permutação
	for (const auto &ciclo : ciclosPermutacao)
	{
		for (int v : ciclo)
		{
			cout << v << " ";
		}
		cout << endl;
	}
}

