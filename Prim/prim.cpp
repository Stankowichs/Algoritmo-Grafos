#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

struct Aresta{
    int u, v;
};

void prim(int n, int inicio, const vector<vector<pair<int,int>>>& grafo, bool mostrar_solucao){
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

        if (u != inicio) {
            arestas_AGM.push_back(make_pair(pai[u], u));
        }

        for (size_t i = 0; i < grafo[u].size(); ++i) {
            int v = grafo[u][i].first;
            int w = grafo[u][i].second;
            if (!visitado[v]) {
                heap.push(make_pair(w, v));
                pai[v] = u;
            }
        }
    }

    cout << custototal << endl;
    /*
    cout << "Arestas na AGM:\n";
    for (size_t i = 0; i < arestas_AGM.size(); ++i) {
        cout << "(" << arestas_AGM[i].first << "," << arestas_AGM[i].second << ") ";
    }
    cout << endl;
    */
    if(mostrar_solucao){
        for(size_t i = 0; i < arestas_AGM.size(); i++){
            cout << "(" << arestas_AGM[i].first << "," << arestas_AGM[i].second << ") ";
        }
    cout << endl;
    }

    ofstream binout("prim.bin", ios::binary);
    for(size_t i = 0; i < arestas_AGM.size(); i++){
        Aresta a = { arestas_AGM[i].first, arestas_AGM[i].second };
        binout.write(reinterpret_cast<const char*>(&a), sizeof(Aresta));
    }
}

int main(int argc, char* argv[]){
    string entrada, saida;
    int inicio = -1;
    bool mostrar_solucao = false;

    for(int i = 1; i < argc; i++){
        string arg = argv[i];
        if(arg == "-h"){
            cout << "Uso: ./prim -f <arquivo> -i <vertice> [-s] [-o <arquivo>] [-h]\n";
            return 0;
        }
        else if(arg == "-f" && i + 1 < argc) entrada = argv[++i];
        else if(arg == "-i" && i + 1 < argc) inicio = stoi(argv[++i]);
        else if(arg == "-s") mostrar_solucao = true;
        else if(arg == "-o" && i + 1 < argc) saida = argv[++i];
    }

    if(entrada.empty()){
        cerr << "Erro: argumentos obrigatorios nao fornecidos. Use -h para ajuda.\n";
        return 0;
    }

    if (inicio == -1) inicio = 1;
    
    ifstream fin(entrada);
    if(!fin){
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 0;
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

    ofstream fout;
    streambuf* coutbuf = cout.rdbuf();
    if(!saida.empty()){
        fout.open(saida);
        if(!fout){
            cerr << "Erro ao abrir arquivo de saída.\n";
            return 1;
        }
        cout.rdbuf(fout.rdbuf());
    }

    prim(n, inicio, grafo, mostrar_solucao);

    if (fout.is_open()) {
        fout.close();
        cout.rdbuf(coutbuf);
    }

    return 0;
}