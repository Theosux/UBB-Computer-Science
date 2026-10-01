#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

// muchie in graful rezidual
struct Muchie {
    int to, cap, flow, rev_idx;
};

vector<vector<Muchie>> adj;
vector<int> in_degree;
vector<int> ordin_topologic;

// kahn pt sortare topologica
void sorteaza_topologic(int V) {
    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ordin_topologic.push_back(u);

        // doar muchiile originale (cap > 0)
        for (const auto& m : adj[u]) {
            if (m.cap > 0) {
                in_degree[m.to]--;
                if (in_degree[m.to] == 0) {
                    q.push(m.to);
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]); 

    int V, E;
    if (!(fin >> V >> E)) return 0;

    adj.resize(V);
    in_degree.assign(V, 0);

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w; 

        int idx_u = adj[u].size();
        int idx_v = adj[v].size();

        // muchia directa + inversa cu cap 0
        adj[u].push_back({ v, w, 0, idx_v });
        adj[v].push_back({ u, 0, 0, idx_u });
        in_degree[v]++; // pt topsort
    }

    int s = 0, t = V - 1;

    // ordinea topologica
    sorteaza_topologic(V);

    vector<int> h(V, 0);  // inaltimi
    vector<long long> e(V, 0); // exces

    h[s] = V;

    // preflux din sursa
    for (auto& m : adj[s]) {
        if (m.cap > 0) {
            int flux_pompat = m.cap;
            m.flow += flux_pompat;
            adj[m.to][m.rev_idx].flow -= flux_pompat;
            e[m.to] += flux_pompat;
            e[s] -= flux_pompat;
        }
    }

    // nodurile in ordine topologica, fara s si t
    for (int u : ordin_topologic) {
        if (u == s || u == t) continue;

        while (e[u] > 0) {
            bool am_pompat = false;

            for (auto& m : adj[u]) {
                // mai e loc pe muchie si vecinul e cu 1 mai jos
                if (m.cap - m.flow > 0 && h[u] == h[m.to] + 1) {
                    long long de_pompat = min(e[u], (long long)(m.cap - m.flow));

                    m.flow += de_pompat;
                    adj[m.to][m.rev_idx].flow -= de_pompat;
                    e[u] -= de_pompat;
                    e[m.to] += de_pompat;

                    am_pompat = true;
                    if (e[u] == 0) break;
                }
            }

            // nu s-a putut pompa -> ridicam nodul
            if (!am_pompat && e[u] > 0) {
                int h_minima = 2e9;
                for (const auto& m : adj[u]) {
                    if (m.cap - m.flow > 0) {
                        h_minima = min(h_minima, h[m.to]);
                    }
                }
                if (h_minima != 2e9) {
                    h[u] = h_minima + 1;
                }
            }
        }
    }

    // fluxul maxim = excesul din t
    fout << e[t] << "\n"; 

    fin.close();
    fout.close();
    return 0;
}