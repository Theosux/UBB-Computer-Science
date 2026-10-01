#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    // arg
    if (argc != 3) {
        cerr << "Utilizare: " << argv[0] << " <fisier_intrare> <fisier_iesire>\n";
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

    // Lista de adiacenta. {nod_destinatie, id_muchie}
    // id - O(1) timp
    vector<vector<pair<int, int>>> adj(V);

    vector<bool> muchie_vizitata(E, false);

    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back({ v, i });
        adj[v].push_back({ u, i });
    }

    // rez final
    vector<int> ciclu;
    vector<int> stiva;

    int start_node = 0;
    for (int i = 0; i < V; ++i) {
        if (!adj[i].empty()) {
            start_node = i;
            break;
        }
    }

    // nod start
    stiva.push_back(start_node);

    // Hierholzer
    while (!stiva.empty()) {
        int u = stiva.back();
        bool muchie_gasita = false;

        while (!adj[u].empty()) {
            pair<int, int> muchie = adj[u].back();
            adj[u].pop_back();

            int v = muchie.first;
            int id = muchie.second;

            if (!muchie_vizitata[id]) {
                muchie_vizitata[id] = true; // vizitata
                stiva.push_back(v);         // noul nod
                muchie_gasita = true;
                break;
            }
        }

        if (!muchie_gasita) {
            ciclu.push_back(u);
            stiva.pop_back(); 
        }
    }

    for (int i = 0; i < ciclu.size(); ++i) {
        fout << ciclu[i] << (i == ciclu.size() - 1 ? "" : " ");
    }
    fout << "\n";

    fin.close();
    fout.close();

    return 0;
}