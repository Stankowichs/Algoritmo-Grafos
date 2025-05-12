#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;

const int INF = numeric_limits<int>::max();

void Dijkstra(int s, const vector<vector<pair<int, int>>>& grafo, ostream& saida){
    int n = grafo.size();
    vector<int> dist(n+1, INF);
    vector<int> prev(n+1, -1);
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> fila;
    fila.push({0, s});

    while(!fila.empty()){
        int u = fila.top().second;
        int d_u = fila.top().first;
        fila.pop();

        if (d_u > dist[u]) continue;

        for(const pair<int, int>& aresta  : grafo[u]){
            int v = aresta.first;
            int peso = aresta.second;
            if(dist[v] > dist[u] + peso){
                dist[v] = dist[u] + peso;
                prev[v] = u;
                fila.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i < n; i++) {
        saida << i << ":";
        if (dist[i] == INF) saida << "-1";
        else saida << dist[i];
        saida << " ";
    }
}

int main(int argc, char* argv[]){
    string entrada, saida;
    bool salvararq;
    int opt;
    int inicio = -1;

    while((opt = getopt(argc, argv, "f:i:o:h")) != -1){
        switch(opt){
            case 'f': entrada = optarg; break;
            case 'i': inicio = stoi(optarg); break;
            case 'o': saida = optarg; salvararq = true; break;
            case 'h':
                cout << "Uso: ./dijkstra.bin -f <arquivo> -i <vertice> [-o <arquivo>] [-h]\n";
                return 0;
            default:
                cerr << "Argumentos invalidos. Use -h para ajuda\n";
                return 1; 
        }
    }

    if(entrada.empty()){
        cerr << "Erro: argumentos obrigatorios nao fornecidos. Use -h para ajuda.\n";
        return 1;
    }

    if (inicio == -1) inicio = 1;

    ifstream fin(entrada);
    if(!fin){
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<pair<int, int>>> grafo(n+1);

    for(int i = 0; i < m; i++){
        int u, v, peso;
        fin >> u >> v >> peso;
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
    }
    fin.close();

    if(salvararq){
        ofstream fout(saida);
        if (!fout) {
            cerr << "Erro ao abrir arquivo de saída.\n";
            return 1;
        }
        Dijkstra(inicio, grafo, fout);
        fout.close();
    } 
    else Dijkstra(inicio, grafo, cout);

    return 0;
}