#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adj; // Lista de adjacência com pares (vizinho, peso)

public:
    // Construtor para inicializar o grafo com N vértices
    Graph(int V) {
        vertices = V;
        adj.resize(V); // Inicializa lista de adjacência com V listas vazias
    }

    void adicionarAresta(int u, int v, int peso) {
        adj[u].push_back({v, peso}); // Adiciona aresta direcionada de u para v com peso
        adj[v].push_back({u, peso}); // Adiciona aresta direcionada de v para u com peso (grafo não direcionado)
    }

    const vector<pair<int, int>>& getAdjacentes(int u) const {
        return adj[u];
    }
};

void dijkstra(const Graph& grafo, vector<int>& dist, vector<int>& prev, int origem) {
    int numVertices = dist.size();
    dist[origem] = 0;

    // Fila de prioridade para armazenar (distância, vértice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second; // Vértice com menor distância
        int d = fila.top().first;  // Distância mínima atual
        fila.pop();

        // Ignora se a distância atual for maior que a registrada
        if (d > dist[u]) continue;

        // Percorre os vizinhos de u
        for (const auto& [vizinho, peso] : grafo.getAdjacentes(u)) {
            if (dist[vizinho] > dist[u] + peso) {
                dist[vizinho] = dist[u] + peso;
                prev[vizinho] = u;
                fila.push({dist[vizinho], vizinho});
            }
        }
    }
}

int main() {
    int v, e;
    cin >> v >> e;

    Graph grafo(v);

    for (int i = 0; i < e; i++) {
        int u, v, peso;
        cin >> u >> v >> peso;
        grafo.adicionarAresta(u, v, peso);
    }

    int origem;
    cin >> origem;

    vector<int> dist(v, numeric_limits<int>::max());
    vector<int> prev(v, -1);

    dijkstra(grafo, dist, prev, origem);

    // Imprime as distâncias mínimas
    for (int i = 0; i < v; i++) {
        cout << "Distância de " << origem << " para " << i << ": " << dist[i] << endl;
    }

    return 0;
}