#include "Grafo.h"
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
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
        replace(line.begin(), line.end(), ',', ' ');
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

    auto inicioPermutacao = high_resolution_clock::now();
    grafo.encontrarCiclosPorPermutacao();
    auto fimPermutacao = high_resolution_clock::now();
    auto duracaoPermutacao = duration_cast<microseconds>(fimPermutacao - inicioPermutacao);
    cout << "Tempo de execução Permutação: " << duracaoPermutacao.count() << " microssegundos" << endl;
}

int main()
{

    processaArquivoCSV("grafo1_5.csv");

	return 0;
}
