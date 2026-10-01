#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int to;
    int weight;
};

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<Edge>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);
    vector<int> minWeight(V, 1e9);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    int startNode = 0;
    pq.push({0, startNode});
    minWeight[startNode] = 0;
    
    long long totalCost = 0;
    vector<pair<int, int>> mstEdges;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        if (parent[u] != -1) {
            totalCost += minWeight[u];
            mstEdges.push_back({min(u, parent[u]), max(u, parent[u])});
        }

        for (auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (!inMST[v] && weight < minWeight[v]) {
                parent[v] = u;
                minWeight[v] = weight;
                pq.push({minWeight[v], v});
            }
        }
    }

    fout << totalCost << "\n";
    fout << mstEdges.size() << "\n";
    // optional se pot sorta ca sa iasa ca in exemplu
    for (auto& p : mstEdges) {
        fout << p.first << " " << p.second << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
