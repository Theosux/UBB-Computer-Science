#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9; // inf

int main(int argc, char* argv[]) {
    // Validarea argumentelor
    if (argc != 3) {
        cerr << "Eroare introdu 2 argumente(fisier intrare si iesire)\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Eroare la deschiderea fisierelor.\n";
        return 1;
    }

    int N, C, D;
    if (!(fin >> N >> C >> D)) return 0;

    int super_sursa = N;       // mod fictiv - camine
    int destinatie = N - 1;    // cladirea centrala
    int V_total = N + 1;       // nr total de noduri

    // 'capacitate' stocheaza reteaua reziduala
    vector<vector<int>> capacitate(V_total, vector<int>(V_total, 0));
    vector<vector<int>> adj(V_total);

    // citim drumurile
    for (int i = 0; i < D; ++i) {
        int u, v, m;
        fin >> u >> v >> m;

        if (capacitate[u][v] == 0 && capacitate[v][u] == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u); 
        }
        capacitate[u][v] += m;
    }

    for (int i = 0; i < C; ++i) {
        adj[super_sursa].push_back(i);
        adj[i].push_back(super_sursa);
        capacitate[super_sursa][i] = INF;
    }

    int flux_maxim = 0;
    vector<int> parent(V_total);

    // Edmonds-Karp
    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;

        q.push(super_sursa);
        parent[super_sursa] = super_sursa;

        // BFS
        while (!q.empty() && parent[destinatie] == -1) {
            int curr = q.front();
            q.pop();

            for (int next : adj[curr]) {
                if (parent[next] == -1 && capacitate[curr][next] > 0) {
                    parent[next] = curr;
                    q.push(next);
                }
            }
        }

        // !destinatie break
        if (parent[destinatie] == -1) {
            break;
        }

        int drum_flux = INF;
        for (int v = destinatie; v != super_sursa; v = parent[v]) {
            int u = parent[v];
            drum_flux = min(drum_flux, capacitate[u][v]);
        }

        for (int v = destinatie; v != super_sursa; v = parent[v]) {
            int u = parent[v];
            capacitate[u][v] -= drum_flux;
            capacitate[v][u] += drum_flux;
        }

        flux_maxim += drum_flux;
    }

    // rez
    fout << flux_maxim << "\n";

    // 2
    for (int i = 0; i < C; ++i) {
        int flux_din_camin = capacitate[i][super_sursa];
        fout << flux_din_camin << (i == C - 1 ? "" : " ");
    }
    fout << "\n";

    fin.close();
    fout.close();

    return 0;
}