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
		else
		{

			if (u != antecessor && find(caminho.begin(), caminho.end(), u) != caminho.end())
			{
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
	if (ciclo.front() != ciclo.back() || ciclo.size() < 4)
		return false;

	for (size_t i = 0; i < ciclo.size() - 1; ++i)
	{

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
		if (!visitado[i])
		{
			dfs(i, visitado, caminho, -1);
		}
	}

	// imprime os ciclos encontrados
	if(imprimirCiclos)
	{
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
}

void Grafo::permutarEVerificarCiclos(vector<int> &vertices, int inicio, set<vector<int>> &ciclosPermutacao, bool imprimirPermutacoes)
{
	if (inicio == vertices.size() - 1)
	{

		if (imprimirPermutacoes)
		{
			// Imprimir a permutação atual dos vértices

			for (int vertice : vertices)
			{
				cout << vertice << " ";
			}
			cout << "\n";
		}

		// verificação de ciclos com o tamanho mínimo de 3
		for (int len = 3; len <= V; ++len)
		{
			vector<int> ciclo(vertices.begin(), vertices.begin() + len);
			ciclo.push_back(ciclo.front());
			if (ehCicloValido(ciclo))
			{
				ciclo.pop_back();
				sort(ciclo.begin(), ciclo.end());
				ciclo.push_back(ciclo.front());

				// verifica se já foi visto esse ciclo antes de imprimir
				if (ciclosPermutacao.insert(ciclo).second && imprimirCiclos)
				{
					for (int vertice : ciclo)
					{
						cout << vertice << " ";
					}
					cout << "\n";
				}
			}
		}
	}
	else
	{
		for (int i = inicio; i < vertices.size(); i++)
		{
			swap(vertices[inicio], vertices[i]);
			permutarEVerificarCiclos(vertices, inicio + 1, ciclosPermutacao, imprimirPermutacoes);
			swap(vertices[inicio], vertices[i]);
		}
	}
}

void Grafo::encontrarCiclosPorPermutacao()
{
	set<vector<int>> ciclosPermutacao;
	vector<int> vertices(V);
	iota(vertices.begin(), vertices.end(), 0);

	permutarEVerificarCiclos(vertices, 0, ciclosPermutacao, imprimirPermutacoes);
}
