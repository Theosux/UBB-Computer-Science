#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

// element pt coada de prioritati
struct Element {
    int cost;
    int nod;
    int parinte;

    // operator > ca sa fie min-heap
    bool operator>(const Element& altul) const {
        return cost > altul.cost;
    }
};

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");

    if (!fin.is_open()) {
        cout << "Eroare! Fisierul in.txt nu a putut fi gasit." << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m; // nr noduri, nr muchii

    // lista de adiacenta, graf[u] = {vecin, cost}
    vector<vector<pair<int, int>>> graf(n + 1);

    // citire graf
    for (int i = 0; i < m; ++i) {
        int u, v, cost;
        fin >> u >> v >> cost;
        // neorientat
        graf[u].push_back({ v, cost });
        graf[v].push_back({ u, cost });
    }

    priority_queue<Element, vector<Element>, greater<Element>> pq;
    vector<bool> vizitat(n + 1, false);

    int cost_total_ama = 0;
    vector<pair<int, int>> muchii_ama;

    // pornim din nodul 1, parinte 0 = fara parinte
    pq.push({ 0, 1, 0 });

    while (!pq.empty()) {
        Element curent = pq.top();
        pq.pop();

        int nod_curent = curent.nod;
        int cost = curent.cost;
        int parinte = curent.parinte;

        // deja vizitat
        if (vizitat[nod_curent]) {
            continue;
        }

        vizitat[nod_curent] = true;
        cost_total_ama += cost;

        // fara muchia de start
        if (parinte != 0) {
            muchii_ama.push_back({ parinte, nod_curent });
        }

        for (auto muchie : graf[nod_curent]) {
            int vecin = muchie.first;
            int cost_muchie = muchie.second;

            if (!vizitat[vecin]) {
                pq.push({ cost_muchie, vecin, nod_curent });
            }
        }
    }

    fout << "Costul total al Arborelui Minim de Acoperire: " << cost_total_ama << "\n";
    fout << "Muchiile care formeaza arborele sunt:\n";
    for (auto muchie : muchii_ama) {
        fout << "Nodul " << muchie.first << " -- Nodul " << muchie.second << "\n";
    }

    fin.close();
    fout.close();

    cout << "Programul s-a executat cu succes! Verifica fisierul out.txt." << endl;

    return 0;
}