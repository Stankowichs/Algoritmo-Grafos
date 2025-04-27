#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) {
        vertices = V;
        adj.resize(V);
    }

    void adicionarAresta(int u, int v, int peso) {
        adj[u].push_back({v, peso});
        adj[v].push_back({u, peso});
    }

    void imprimir() {
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (auto vizinho : adj[i]) {
                cout << "(" << vizinho.first << ", " << vizinho.second << ") ";
            }
            cout << endl;
        }
    }

    const vector<vector<pair<int, int>>>& getAdj() const {
        return adj;
    }
};

void dijkstra(const vector<vector<pair<int, int>>> &graph, vector<int>& dist, vector<int> &prev, int origem) {

    int numVertices = graph.size();
    dist[origem] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        int distAtual = fila.top().first;
        int vertice = fila.top().second;
        fila.pop();

        if (distAtual > dist[vertice]) continue;

        for (auto vizinho : graph[vertice]) {
            int peso = vizinho.second;
            int verticeVizinho = vizinho.first;

            if (dist[verticeVizinho] > dist[vertice] + peso) {
                dist[verticeVizinho] = dist[vertice] + peso;
                prev[verticeVizinho] = vertice;
                fila.push({dist[verticeVizinho], verticeVizinho});
            }
        }
    }
}

int main() {
    int v, e;
    cin >> v >> e;

    Graph grafo(v);

    for (int i = 0; i < e; i++) {
        int u, w, peso;
        cin >> u >> w >> peso;
        grafo.adicionarAresta(u-1, w-1, peso);
    }

    vector<int> prev(v, -1);
    vector<int> dist(v, numeric_limits<int>::max());

    dijkstra(grafo.getAdj(), dist, prev, 0);

    for (int i = 0; i < v; i++) {
        // cout << "Distancia de 0 para " << i << ": " << dist[i] << endl;
        cout << (dist[i] == numeric_limits<int>::max() ? -1 : dist[i]) << " "; // Se a distância for infinita, imprime -1
    }

    return 0;
}
