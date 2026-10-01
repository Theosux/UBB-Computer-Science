#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    // arg
    if (argc != 3) {
        cerr << "Introduce 2 arg (fila de intrare si iesire)\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Eroare la deschiderea fisierelor.\n";
        return 1;
    }

    int N, M;
    if (!(fin >> N >> M)) return 0;

    vector<vector<int>> adj(N);
    vector<int> grad(N, 0);

    for (int i = 0; i < M; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        grad[u]++;
        grad[v]++;
    }

    // vector 0 - N-1
    vector<int> noduri(N);
    for (int i = 0; i < N; ++i) {
        noduri[i] = i;
    }

    // Euristica Welsh-Powell
    sort(noduri.begin(), noduri.end(), [&](int a, int b) {
        return grad[a] > grad[b];
        });

    // vector culoare
    vector<int> culori(N, -1);
    int max_culoare = -1;

    for (int i = 0; i < N; ++i) {
        int u = noduri[i];

        vector<bool> culori_folosite(N, false);

        for (int vecin : adj[u]) {
            if (culori[vecin] != -1) {
                culori_folosite[culori[vecin]] = true; // marcam culoarea
            }
        }

        // cautam cea mai mica culoare
        int c = 0;
        while (culori_folosite[c] == true) {
            c++;
        }

        // atribuim
        culori[u] = c;
        if (c > max_culoare) {
            max_culoare = c;
        }
    }

    // nr total de culori
    int C = max_culoare + 1;

    // write
    fout << C << "\n";
    for (int i = 0; i < N; ++i) {
        fout << culori[i] << (i == N - 1 ? "" : " ");
    }
    fout << "\n";

    fin.close();
    fout.close();

    return 0;
}