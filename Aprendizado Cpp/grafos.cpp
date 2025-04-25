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
        graph[w].push_back(u);
        graph[u].push_back(w);
    }

    for(int i = 0; i < v; i++){
        cout << "Vertice do vertice " << i << ": ";
        for(int vizinhos : graph[i]) 
            cout << vizinhos << " ";
        cout << endl;
    }

    return 0;
}