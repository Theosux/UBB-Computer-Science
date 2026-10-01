#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

// Structura vecin
struct Vecin {
    int to, w;
};

// Structura muchie
struct MuchieSelectata {
    int u, v, w;
    //suprascriere operator min-heap
    bool operator>(const MuchieSelectata& alta) const {
        return w > alta.w;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<Vecin>> adj(V);//lista de adiacenta vecini
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    vector<bool> vizitat(V, false);//vector vizitat
    priority_queue<MuchieSelectata, vector<MuchieSelectata>, greater<MuchieSelectata>> pq;//priority_queqe

    long long cost_total = 0;
    vector<pair<int, int>> arbore_minim;

    // pornim din nodu 1
    vizitat[0] = true;
    // Punem in coada toate muchiile care pleaca din nodu 0
    for (const auto& vecin : adj[0]) {
        pq.push({ 0, vecin.to, vecin.w });
    }

    // extindem arborele pana la V-1 muchii
    while (!pq.empty() && arbore_minim.size() < V - 1) {
        MuchieSelectata curent = pq.top();
        pq.pop();

        // Daca nodul destinatie este deja vizitat, sarim peste
        if (vizitat[curent.v]) continue;

        // Adaugam muchia in arbore
        vizitat[curent.v] = true;
        cost_total += curent.w;

        // Salvam nodurile in ordine crescatoare pe linie
        arbore_minim.push_back({ min(curent.u, curent.v), max(curent.u, curent.v) });

        // Adaugam in coada toate muchiile care pleaca din nodul proaspat vizitat
        for (const auto& vecin : adj[curent.v]) {
            if (!vizitat[vecin.to]) {
                pq.push({ curent.v, vecin.to, vecin.w });
            }
        }
    }
    sort(arbore_minim.begin(), arbore_minim.end());
    fout << cost_total << "\n" << arbore_minim.size() << "\n";
    for (int i = 0; i < arbore_minim.size(); ++i) {
        fout << arbore_minim[i].first << " " << arbore_minim[i].second << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}