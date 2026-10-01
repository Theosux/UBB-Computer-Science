#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

bool bfs(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t) return true;
                q.push({v, new_flow});
            }
        }
    }
    return false;
}

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<int>> capacity(V, vector<int>(V, 0));
    vector<vector<int>> adj(V);

    for (int i = 0; i < E; ++i) {
        int u, v, c;
        fin >> u >> v >> c;
        capacity[u][v] += c;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    int s = 0, t = V - 1;
    long long max_flow = 0;
    vector<int> parent(V);

    while (bfs(s, t, capacity, adj, parent)) {
        int flow = INF;
        int curr = t;
        while (curr != s) {
            int p = parent[curr];
            flow = min(flow, capacity[p][curr]);
            curr = p;
        }

        max_flow += flow;
        curr = t;
        while (curr != s) {
            int p = parent[curr];
            capacity[p][curr] -= flow;
            capacity[curr][p] += flow;
            curr = p;
        }
    }

    fout << max_flow << "\n";

    fin.close();
    fout.close();
    return 0;
}
