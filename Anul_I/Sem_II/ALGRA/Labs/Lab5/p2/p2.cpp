#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    // argumentele
    if (argc != 3) {
        cerr << "Eroare: introduce fisier intrare si iesire(2 argumente).\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Eroare la deschiderea fisierelor.\n";
        return 1;
    }

    int V, E;
    if (!(fin >> V >> E)) return 0;

    // reziduala 
    vector<vector<int>> capacitate(V, vector<int>(V, 0));
    // lista de adiacenta
    vector<vector<int>> adj(V);

    for (int i = 0; i < E; ++i) {
        int u, v, c;
        fin >> u >> v >> c;

        // repetare
        if (capacitate[u][v] == 0 && capacitate[v][u] == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u); // inv
        }
        capacitate[u][v] += c;
    }

    int sursa = 0;
    int sink = V - 1;

    // inaltim si exces
    vector<int> h(V, 0);
    vector<long long> e(V, 0);

    queue<int> active; // supraincarcarea
    vector<bool> in_queue(V, false);

    // preflux
    h[sursa] = V; // sursa - inaltime v

    for (int v : adj[sursa]) {
        int cap = capacitate[sursa][v];
        if (cap > 0) {
            capacitate[sursa][v] -= cap;
            capacitate[v][sursa] += cap;
            e[v] += cap;
            e[sursa] -= cap;

            // adaugam noduri active valide
            if (v != sursa && v != sink && !in_queue[v]) {
                active.push(v);
                in_queue[v] = true;
            }
        }
    }

    // descarcare
    while (!active.empty()) {
        int u = active.front(); // nod supraincarcat

        // Atata timp cat nodul 'u' are exces de flux
        while (e[u] > 0) {
            bool pushed = false;

            for (int v : adj[u]) {
                if (capacitate[u][v] > 0 && h[u] == h[v] + 1) {
                    long long push_val = min((long long)capacitate[u][v], e[u]);

                    // actualizam
                    capacitate[u][v] -= push_val;
                    capacitate[v][u] += push_val;
                    e[u] -= push_val;
                    e[v] += push_val;

                    // v - supraincarcat
                    if (v != sursa && v != sink && !in_queue[v]) {
                        active.push(v);
                        in_queue[v] = true;
                    }

                    pushed = true;
                    if (e[u] == 0) break;
                }
            }

            // inaltam nodul
            if (!pushed) {
                int min_h = 1e9;
                for (int v : adj[u]) {
                    if (capacitate[u][v] > 0) {
                        min_h = min(min_h, h[v]);
                    }
                }
                h[u] = min_h + 1;
            }
        }

        // eliminam nodul
        active.pop();
        in_queue[u] = false;
    }

    fout << e[sink] << "\n";

    fin.close();
    fout.close();

    return 0;
}