#include <iostream>
#include <vector>

using namespace std;

int main(){
    int v, e;
    cin >> v >> e;

    vector<vector<int>> graph(v, vector<int>());

    for(int i = 0; i < e; i++){
        int w, u;
        cin >> w >> u;
        graph[w-1].push_back(u-1);
        graph[u-1].push_back(w-1);
    }

    for(int i = 0; i < v; i++){
        int somaVizinhos = 0;

        for(int vizinhos : graph[i]) {
            for(int vizinhos2 : graph[vizinhos]) {
                somaVizinhos++;
            }
        }

        cout << somaVizinhos << " ";
    }

    return 0;
}