#include "Grafo.h"
#include<iostream>
#include<chrono>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>


using namespace std;
using namespace std::chrono;


Grafo* processarArquivoCSV(const string& nomeArquivo){
	Grafo* grafo = nullptr;
	bool leuCabecalho = false;

	ifstream file(nomeArquivo);
	string linha;

	if(!file.is_open()){
		throw runtime_error("Não foi possível abrir o arquivo: " + nomeArquivo);
	}
	while(getline(file,linha)){
		if(!leuCabecalho){
			if(linha.find("# Verticees:") == 0 && !grafo){
				int numVertices = std::stoi(linha.substr(linha.find(":") + 1 ));
				grafo = new Grafo(numVertices);
			}else if(linha.find("# Arestas:") == 0){
				leuCabecalho = true;
			}
		}else{
			istringstream iss(linha);
			string item;
			vector<std::string> dados;

			while(getline(iss, item, ',' )){
				dados.push_back(item);
			}
		}
	}
}

int main()
{
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

	return 0;
}
