#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int flow;
    int cap;
    int rev_index;
};

void push(int u, int edge_idx, vector<vector<Edge>>& adj, vector<int>& excess) {
    Edge& e = adj[u][edge_idx];
    int push_val = min(excess[u], e.cap - e.flow);
    e.flow += push_val;
    adj[e.to][e.rev_index].flow -= push_val;
    excess[u] -= push_val;
    excess[e.to] += push_val;
}

void relabel(int u, vector<vector<Edge>>& adj, vector<int>& height) {
    int min_h = 1e9;
    for (const auto& e : adj[u]) {
        if (e.cap - e.flow > 0) {
            min_h = min(min_h, height[e.to]);
        }
    }
    if (min_h != 1e9) {
        height[u] = min_h + 1;
    }
}

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<Edge>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v, c;
        fin >> u >> v >> c;
        adj[u].push_back({v, 0, c, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
    }

    int s = 0, t = V - 1;
    vector<int> height(V, 0);
    vector<int> excess(V, 0);

    height[s] = V;
    for (auto& e : adj[s]) {
        int push_val = e.cap;
        e.flow += push_val;
        adj[e.to][e.rev_index].flow -= push_val;
        excess[s] -= push_val;
        excess[e.to] += push_val;
    }

    queue<int> active;
    for (int i = 0; i < V; ++i) {
        if (i != s && i != t && excess[i] > 0) {
            active.push(i);
        }
    }

    while (!active.empty()) {
        int u = active.front();
        active.pop();

        while (excess[u] > 0) {
            bool pushed = false;
            for (size_t i = 0; i < adj[u].size(); ++i) {
                if (adj[u][i].cap - adj[u][i].flow > 0 && height[u] == height[adj[u][i].to] + 1) {
                    push(u, i, adj, excess);
                    pushed = true;
                    if (adj[u][i].to != s && adj[u][i].to != t && excess[adj[u][i].to] > 0) {
                        active.push(adj[u][i].to);
                    }
                    if (excess[u] == 0) break;
                }
            }
            if (!pushed) {
                relabel(u, adj, height);
            }
        }
    }

    fout << excess[t] << "\n";

    fin.close();
    fout.close();
    return 0;
}
