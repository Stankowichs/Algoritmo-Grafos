#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;

void prim(int n, int inicio, const vector<vector<pair<int,int>>>& grafo, ostream& saida, bool mostrar_solucao){
    vector<bool> visitado(n+1, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater <pair<int,int>>> heap;
    vector<int> pai(n + 1, -1);
    vector<pair<int,int>> arestas_AGM;

    int custototal = 0;
    heap.push(make_pair(0, inicio));

    while(!heap.empty()){
        int peso = heap.top().first;
        int u = heap.top().second;
        heap.pop();

        if(visitado[u]) continue;

        visitado[u] = true;
        custototal += peso;

        if (u != inicio) arestas_AGM.push_back(make_pair(pai[u], u));

        for (size_t i = 0; i < grafo[u].size(); ++i) {
            int v = grafo[u][i].first;
            int w = grafo[u][i].second;
            if (!visitado[v]) {
                heap.push(make_pair(w, v));
                pai[v] = u;
            }
        }
    }

    if(mostrar_solucao){
        for(size_t i = 0; i < arestas_AGM.size(); i++){
            saida << "(" << arestas_AGM[i].first << "," << arestas_AGM[i].second << ") ";
        }
        saida << endl;
    }
    else saida << custototal << endl;
}

int main(int argc, char* argv[]){
    string entrada, saida;
    int inicio = -1;
    bool mostrar_solucao = false;
    bool salvararq = false;
    int opt;

    while((opt = getopt(argc, argv, "f:i:o:sh")) != -1){
        switch(opt){
            case 'f': entrada = optarg; break;
            case 'i': inicio = stoi(optarg); break;
            case 'o': saida = optarg; salvararq = true; break;
            case 's': mostrar_solucao = true; break;
            case 'h':
                cout << "Uso: ./prim.bin -f <arquivo> -i <vertice> [-s] [-o <arquivo>] [-h]\n";
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
    vector<vector<pair<int,int>>> grafo(n+1);

    for(int i = 0; i < m; i++){
        int u, v, peso;
        fin >> u >> v >> peso;
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
    }
    fin.close();

    if(salvararq){
        ofstream fout(saida);
        if(!fout.is_open()){
            cerr << "Erro ao abrir arquivo de saida.\n";
            return 1;
        }
        prim(n, inicio, grafo, fout, mostrar_solucao);
        fout.close();
    }
    else prim(n, inicio, grafo, cout, mostrar_solucao);

    return 0;
}