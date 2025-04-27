#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int cnt = 0;
void bfs(vector<vector<int>> &graph, vector<int> &pre, vector<int> &pai, vector<int> &dist, int v){
    pre[v] = cnt++;
    dist[v] = 0;
    queue<int> fila;
    fila.push(v);

    while(!fila.empty()){
        int s = fila.front();
        fila.pop();

        for(int vizinho : graph[s]){
            if(pre[vizinho] == -1){
                pre[vizinho] = cnt++;
                pai[vizinho] = s;
                dist[vizinho] = dist[s] + 1;
                fila.push(vizinho);
            }
        } 
    }
}

void imprimirGrafo(vector<vector<int>> graph){
    for(int i = 0; i < graph.size(); i++){
        cout << "Vertice " << i << ": ";
        for(int vizinhos : graph[i]) 
            cout << vizinhos << " ";
        cout << endl;
    }
}

int main(){

    int v, e;
    cin >> v >> e;

    vector<vector<int>> graph(v, vector<int>());

    for(int i = 0; i < e; i++){
        int u, w;
        cin >> u >> w;

        graph[u-1].push_back(w-1);
    }

    vector<int> pre(v, -1);
    vector<int> pai(v, -1);
    vector<int> dist(v, -1);

    pai[0] = -1;

    bfs(graph, pre, pai, dist, 0);

    for(int i = 0; i < v; i++)
        cout << dist[i] << " ";

    return 0;
}