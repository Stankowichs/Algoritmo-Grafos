#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <tuple>
#include <algorithm>
#include <functional>

using namespace std;

int find(int v, vector<int>& pai){
    if(pai[v] != v) pai[v] = find(pai[v], pai);
    return pai[v];
}

void union_(int a, int b, vector<int>& pai, vector<int>& rank){
    a = find(a, pai);
    b = find(b, pai);

    if(rank[a] >= rank[b]){
        pai[b] = a;
        if(rank[a] == rank[b]) rank[a]++;
    }
    else pai[a] = b;
}

void kruskal(int n, const vector<vector<pair<int, int>>>& grafo, ostream& saida, bool mostrar_solucao){
    vector<pair<int, int>> arestas_AGM;
    int custototal = 0;

    vector<int> pai(n + 1), rank(n + 1, 0);
    for(int i = 1; i <= n; i++) pai[i] = i;

    vector<tuple<int, int, int>> arestas;

    for(int u = 1; u <= n; u++){
        for(size_t j = 0; j < grafo[u].size(); ++j){
            int v = grafo[u][j].first;
            int peso = grafo[u][j].second;
            if(u < v) arestas.push_back(make_tuple(peso, u , v));
        }
    }
    sort(arestas.begin(), arestas.end());

    for(size_t i = 0; i < arestas.size(); ++i){
        int peso = get<0>(arestas[i]);
        int u = get<1>(arestas[i]);
        int v = get<2>(arestas[i]);

        if(find(u, pai) != find(v, pai)){
            arestas_AGM.push_back(make_pair(u, v));
            custototal += peso;

            union_(u, v, pai, rank);
        }
    }

    if(mostrar_solucao == true){
        for(size_t i = 0; i < arestas_AGM.size(); ++i){
            saida << "(" << arestas_AGM[i].first << "," << arestas_AGM[i].second << ") ";
        }
        saida << "\n";
    }
    else{
        saida << custototal << "\n";
    }
}

int main(int argc, char* argv[]){
    string entrada, saida;
    bool salvararq = false;
    bool mostrar_solucao = false;
    int opt;

    while((opt = getopt(argc, argv, "f:o:sh")) != -1){
        switch(opt){
            case 'f': entrada = optarg; break;
            case 'o': saida = optarg; salvararq = true; break;
            case 's': mostrar_solucao = true; break;
            case 'h':
                cout << "Uso: ./kruskal.bin -f <arquivo> [-s] [-o <arquivo>] [-h]\n";
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
        kruskal(n, grafo, fout, mostrar_solucao);
        fout.close();
    }
    else kruskal(n, grafo, cout, mostrar_solucao);

    return 0;
}