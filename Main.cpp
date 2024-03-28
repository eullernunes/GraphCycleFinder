#include "Grafo.h"
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>


using namespace std;
using namespace std::chrono;

void processaArquivoCSV(const std::string &arquivo)
{
	ifstream file(arquivo);
	string line;

	// Ignora as duas primeiras linhas com os comentários
	getline(file, line);
	int V = stoi(line.substr(line.find(':') + 1).c_str());

	Grafo grafo(V);

	getline(file, line);


	// Lê as arestas
	while (getline(file, line))
	{
		replace(line.begin(), line.end(), ',',  ' ');
		istringstream iss(line);
		int v, w;
		if (iss >> v >> w)
		{
			grafo.addAresta(v, w);
		}
	}

	file.close();

	auto inicioDfs = high_resolution_clock::now();
	grafo.encontrarCiclosDfs();
	auto fimDFS = high_resolution_clock::now();
	auto duracaoDFS = duration_cast<microseconds>(fimDFS - inicioDfs);
	cout << "Tempo de execução DFS: " << duracaoDFS.count() << " microssegundos" << endl;

	// Medindo o tempo de execução da Permutação
	auto inicioPermutacao = high_resolution_clock::now();
	grafo.encontrarCiclosPorPermutacao();
	auto fimPermutacao = high_resolution_clock::now();
	auto duracaoPermutacao = duration_cast<microseconds>(fimPermutacao - inicioPermutacao);
	cout << "Tempo de execução Permutação: " << duracaoPermutacao.count() << " microssegundos" << endl;
}

int main()
{

	processaArquivoCSV("grafo1_4.csv");

	/*
		Grafo g(5); // Criando um grafo com 5 vértices
		g.addAresta(0, 1);
		g.addAresta(1, 2);
		g.addAresta(2, 0);
		g.addAresta(1, 3);
		g.addAresta(3, 4);
		g.addAresta(4, 1);

		auto inicioDfs = high_resolution_clock::now();
		g.encontrarCiclosDfs();
		auto fimDFS = high_resolution_clock::now();
		auto duracaoDFS = duration_cast<microseconds>(fimDFS - inicioDfs);
		cout << "Tempo de execução DFS: " << duracaoDFS.count() << " microssegundos" << endl;

		// Medindo o tempo de execução da Permutação
		auto inicioPermutacao = high_resolution_clock::now();
		g.encontrarCiclosPorPermutacao();
		auto fimPermutacao = high_resolution_clock::now();
		auto duracaoPermutacao = duration_cast<microseconds>(fimPermutacao - inicioPermutacao);
		cout << "Tempo de execução Permutação: " << duracaoPermutacao.count() << " microssegundos" << endl;
	*/
/*
	try
	{
		Grafo *grafo = processarArquivoCSV("grafo2_4.csv");

		if (grafo != nullptr)
		{
			auto inicioDfs = high_resolution_clock::now();
			grafo->encontrarCiclosDfs();
			auto fimDFS = high_resolution_clock::now();
			auto duracaoDFS = duration_cast<microseconds>(fimDFS - inicioDfs);
			cout << "Tempo de execução DFS: " << duracaoDFS.count() << " microssegundos" << endl;

			// Medindo o tempo de execução da Permutação
			auto inicioPermutacao = high_resolution_clock::now();
			grafo->encontrarCiclosPorPermutacao();
			auto fimPermutacao = high_resolution_clock::now();
			auto duracaoPermutacao = duration_cast<microseconds>(fimPermutacao - inicioPermutacao);
			cout << "Tempo de execução Permutação: " << duracaoPermutacao.count() << " microssegundos" << endl;

			delete grafo;
		}
		else
		{
			cerr << "Falha ao criar o grafo a partir do arquivo CSV." << endl;
		}
	}
	catch (const exception &e)
	{
		cerr << "Erro: " << e.what() << endl;
	}
*/
	return 0;
}
