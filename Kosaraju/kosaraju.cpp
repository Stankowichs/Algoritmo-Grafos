#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <stack>

using namespace std;

void DFS(int v, const vector<vector<int>>& grafo, vector<bool>& visitado, stack<int>& posordem){
    visitado[v] = true;
    for(int u : grafo[v]){
        if(!visitado[u]) DFS(u, grafo, visitado, posordem);
    }
    posordem.push(v);
}

void DFSt(int v, const vector<vector<int>>& grafoT, vector<bool>& visitado, vector<int>& componente){
    visitado[v] = true;
    componente.push_back(v);
    for(int u : grafoT[v]){
        if(!visitado[u]) DFSt(u, grafoT, visitado, componente);
    }
}

void kosaraju(int n, const vector<vector<int>>& grafo, ostream& saida){
    vector<bool> visitado(n+1, false);
    stack<int> posordem;

    for(int i = 1; i <= n; i++){
        if(!visitado[i]) DFS(i, grafo, visitado, posordem);
    }

    vector<vector<int>> grafoT(n+1);
    for(int u = 1; u <= n; u++){
        for(int v : grafo[u]){
            grafoT[v].push_back(u);
        }
    }

    fill(visitado.begin(), visitado.end(), false);

    while(!posordem.empty()){
        int v = posordem.top();
        posordem.pop();

        if(!visitado[v]){
            vector<int> componente;
            DFSt(v, grafoT, visitado, componente);

            for(int x : componente){
                saida << x << " ";
            }
            saida << endl;
        }
    }
}

int main(int argc, char* argv[]){
    string entrada, saida;
    bool salvararq = false;
    int opt;

    while((opt = getopt(argc, argv, "f:o:h")) != -1){
        switch(opt){
            case 'f': entrada = optarg; break;
            case 'o': saida = optarg; salvararq = true; break;
            case 'h':
                cout << "Uso: ./kosaraju.bin -f <arquivo> [-o <arquivo>] [-h]\n";
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
    vector<vector<int>> grafo(n+1);

    for(int i = 0; i < m; i++){
        int u, v;
        fin >> u >> v;
        grafo[u].push_back(v);
    }
    fin.close();

    if(salvararq){
        ofstream fout(saida);
        if(!fout.is_open()){
            cerr << "Erro ao abrir arquivo de saida.\n";
            return 1;
        }
        kosaraju(n, grafo, fout);
        fout.close();
    }
    else kosaraju(n, grafo, cout);

    return 0;
}