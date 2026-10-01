#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;
//idee :fiecare intersectie are un rezervor propriu,si fiecare nod este la o anumita inaltime
//daca 
int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<int>> cap(V, vector<int>(V, 0));//capacitate maxima tevi
    vector<vector<int>> flow(V, vector<int>(V, 0));//apa care curge pe tevi
    vector<vector<int>> adj(V);//

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] += w;
    }

    int s = 0, t = V - 1;
    vector<int> h(V, 0);//inaltime 
    vector<int> e(V, 0);//exces apa

    h[s] = V;//sursa e ridicata cel mai sus
    queue<int> q; //
    vector<bool> in_coada(V, false);

    for (int v : adj[s]) {
        if (cap[s][v] > 0) {
            flow[s][v] = cap[s][v];//punem maxim pe teava
            flow[v][s] = -flow[s][v];//intoarcere
            e[v] = cap[s][v];//vecinii primesc aceasta apa
            e[s] -= cap[s][v];

            if (v != s && v != t && !in_coada[v]) {
                q.push(v);
                in_coada[v] = true;
            }
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_coada[u] = false;
        for (int v : adj[u]) {
            if (e[u] == 0) break; 
 
            if (cap[u][v] - flow[u][v] > 0 && h[u] == h[v] + 1) {//pompeaza daca este spatiu pe teava si nodul dest este o treapta mai jos
                int apa_pompata = min(e[u], cap[u][v] - flow[u][v]);

                flow[u][v] += apa_pompata;
                flow[v][u] -= apa_pompata;
                e[u] -= apa_pompata;
                e[v] += apa_pompata;

                if (v != s && v != t && !in_coada[v]) {
                    q.push(v);
                    in_coada[v] = true;
                }
            }
        }
        if (e[u] > 0) {//inaltare daca am ramas cu apa in exces,luam vecinul cu inaltime cea mai mica si il urcam
            int h_minima = 2e9;
            for (int v : adj[u]) {
                if (cap[u][v] - flow[u][v] > 0) {
                    h_minima = min(h_minima, h[v]);
                }
            }
            h[u] = h_minima + 1;
            q.push(u);
            in_coada[u] = true;
        }
    }

    fout << e[t] << "\n";

    fin.close();
    fout.close();
    return 0;
}