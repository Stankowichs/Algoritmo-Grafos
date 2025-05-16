#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <unistd.h>

using namespace std;

const int INF = numeric_limits<int>::max();

void floydwarshall(int n, vector<vector<int>>& dist, ostream& saida){
    for(int i = 1; i <= n; i++) dist[i][i] = 0;

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(dist[i][k] < INF && dist[k][j]< INF){
                    if(dist[i][k] + dist[k][j] < dist[i][j]) dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(int i = 1; i <= n; i++){
        if(dist[i][i] < 0){
            saida << "Ciclo negativo detectado" << "\n";
            return;
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(dist[i][j] == INF) saida << "- ";
            else saida << dist[i][j] << " ";
        }
        saida << endl;
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
                cout << "Uso: ./floydwarshall.bin -f <arquivo> [-o <arquivo>] [-h]\n";
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
    vector<vector<int>> dist(n+1, vector<int>(n+1, INF));

    for(int i = 0; i < m; i++){
        int u, v, peso;
        fin >> u >> v >> peso;
        dist[u][v] = peso;
    }
    fin.close();

    if(salvararq){
        ofstream fout(saida);
        if(!fout.is_open()){
            cerr << "Erro ao abrir arquivo de saida.\n";
            return 1;
        }
        floydwarshall(n, dist, fout);
        fout.close();
    }
    else floydwarshall(n, dist, cout);

    return 0;
}