#include <vector>
#include "Grafo.h"
#include <set>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

Grafo::Grafo(int V)
{
	this->V = V;
	adjMatriz = vector<vector<bool>>(V, vector<bool>(V, false));
}

void Grafo::addAresta(int v, int w)
{
	adjMatriz[v][w] = true;
	adjMatriz[w][v] = true;
}

void Grafo::dfs(int v, vector<bool> &visitado, vector<int> &caminho, int antecessor)
{
	visitado[v] = true;
	caminho.push_back(v);

	for (int u = 0; u < V; ++u)
	{
		if (adjMatriz[v][u])
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
	}
	caminho.pop_back();
	visitado[v] = false;
}

bool Grafo::ehCicloValido(const vector<int> &ciclo)
{
	if (ciclo.front() != ciclo.back() || ciclo.size() < 3)
		return false;

	for (size_t i = 0; i < ciclo.size() - 1; ++i)
	{
		if (!adjMatriz[ciclo[i]][ciclo[i + 1]])
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
