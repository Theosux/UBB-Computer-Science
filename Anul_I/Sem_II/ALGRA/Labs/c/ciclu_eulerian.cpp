#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vector<bool> edge_visited(E, false);
    vector<int> euler_path;
    stack<int> st;

    st.push(0);

    while (!st.empty()) {
        int u = st.top();
        bool has_unvisited_edge = false;
        
        while (!adj[u].empty()) {
            auto edge = adj[u].back();
            adj[u].pop_back();
            if (!edge_visited[edge.second]) {
                edge_visited[edge.second] = true;
                st.push(edge.first);
                has_unvisited_edge = true;
                break;
            }
        }

        if (!has_unvisited_edge) {
            euler_path.push_back(u);
            st.pop();
        }
    }

    for (size_t i = 0; i < euler_path.size(); ++i) {
        fout << euler_path[i] << (i + 1 == euler_path.size() ? "" : " ");
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}
