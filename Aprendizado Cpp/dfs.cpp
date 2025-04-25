#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;

void dfsRec(vector<vector<int>> &graph, int v, vector<int> &pre){

    pre[v] = cnt++;
    for(int vizinho : graph[v]){
        if(pre[vizinho] == -1)
            dfsRec(graph, vizinho, pre);
    }
}

void dfs(vector<vector<int>> &graph, vector<int> &pre){

    for(int v = 0; v < graph.size(); v++){
        if(pre[v] == -1)
            dfsRec(graph, v, pre);
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

    // Adicionando arestas ao grafo 
    // O grafo é não direcionado, então adicionamos as arestas em ambas as direções
    for(int i = 1; i < e; i++){
        int u, w;
        cin >> u >> w;
        graph[u].push_back(w); 
        graph[w].push_back(u); 
    }
    
    vector<int> pre(v, -1);
    // imprimirGrafo(graph);

    dfs(graph, pre);
    for(int i = 0; i < v; i++)
        cout << "Vertice " << i << " pre " << pre[i] << endl;

    cout << graph.size() << v << endl;

    return 0;
}