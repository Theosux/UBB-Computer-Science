#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;
int cap[1005][1005];
vector<vector<int>> adj;
vector<int> tata;
int bfs(int s, int t) {
    fill(tata.begin(), tata.end(), -1);
    queue<int> q;

    q.push(s);
    tata[s] = s;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (tata[v] == -1 && cap[u][v] > 0) {
                tata[v] = u;

                // daca am ajuns la destinatie 
                if (v == t) {
                    int flux_minim = 2e9;

                    // cautam minimu
                    for (int curr = t; curr != s; curr = tata[curr]) {
                        int prev = tata[curr];
                        flux_minim = min(flux_minim, cap[prev][curr]);
                    }

                    // trecem prin drum  si actualizam fluxul
                    for (int curr = t; curr != s; curr = tata[curr]) {
                        int prev = tata[curr];
                        cap[prev][curr] -= flux_minim;
                        cap[curr][prev] += flux_minim;
                    }

                    return flux_minim;
                }

                q.push(v);
            }
        }
    }
    return 0; 
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;
    adj.resize(V);
    tata.resize(V);

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = w;
    }

    int flux_maxim = 0;

    while (true) {
        int flux_curent = bfs(0, V - 1);
        if (flux_curent == 0) break;
        flux_maxim += flux_curent;
    }

    fout << flux_maxim << "\n";

    fin.close();
    fout.close();
    return 0;
}