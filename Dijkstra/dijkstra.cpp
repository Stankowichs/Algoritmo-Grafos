#include <iostream>
#include <vector>
#include <queue>
#include <limits>

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

    vector<vector<pair<int, int>>> getAdj() {
        return adj;
    }
};

void dijkstra(vector<vector<pair<int, int>>> &graph, vector<int>& dist, vector<int> &prev, int origem) {
    int numVertices = graph.size();
    dist[origem] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        int d = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (d > dist[u]) continue;

        for (auto [v, peso] : graph[u]) {
            if (dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                prev[v] = u;
                fila.push({dist[v], v});
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
        grafo.adicionarAresta(u, w, peso);
    }

    vector<int> prev(v, -1);
    vector<int> dist(v, numeric_limits<int>::max());

    dijkstra(grafo.getAdj(), dist, prev, 0);

    for (int i = 0; i < v; i++) {
        cout << "Distância de 0 para " << i << ": " << dist[i] << endl;
    }
}
