#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

struct Muchie {													// retinem mai usor muchiile
	int u, v, w;
	bool operator<(const Muchie& other) const {					// pt a putea sorta muchiile mai usor
		if (u != other.u) return u < other.u;
		return v < other.v;
	}
};

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Introduceti fisier intrare fisier iesire\n";
		return 1;
	}

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	if (!fin.is_open() || !fout.is_open()) {
		cerr << "Eroare deschidere fisiere.\n";
		return 1;
	}

	int V, E;
	if (!(fin >> V >> E)) return 0;

	vector<Muchie> muchii(E);
	for (int i = 0; i < E; i++) {
		fin >> muchii[i].u >> muchii[i].v >> muchii[i].w;
	}
	//Bellman-Ford
	vector<int> h(V, 0);

	for (int i = 1; i < V; i++) {
		bool any_relaxed = false;
		for (const auto& muchie : muchii) {
			if (h[muchie.u] != INF && h[muchie.u] + muchie.w < h[muchie.v]) {
				h[muchie.v] = h[muchie.u] + muchie.w;
				any_relaxed = true;
			}
		}
		if (!any_relaxed) break;
	}

    bool neg_cycle = false;
    for (const auto& muchie : muchii) {
        if (h[muchie.u] != INF && h[muchie.u] + muchie.w < h[muchie.v]) {
            neg_cycle = true;
            break;
        }
    }

    // Pt ciclu negativ negativ afisam -1
    if (neg_cycle) {
        fout << "-1\n";
        fin.close();
        fout.close();
        return 0;
    }

    // reponderarea muchiilor
    vector<Muchie> muchii_noi = muchii;
    for (int i = 0; i < E; ++i) {
        muchii_noi[i].w = muchii[i].w + h[muchii[i].u] - h[muchii[i].v];
    }

    sort(muchii_noi.begin(), muchii_noi.end());

    for (int i = 0; i < E; ++i) {
        fout << muchii_noi[i].u << " " << muchii_noi[i].v << " " << muchii_noi[i].w << "\n";
    }

    // pregatim dijkstra
    vector<vector<pair<int, int>>> adj(V);
    for (const auto& muchie : muchii_noi) {
        adj[muchie.u].push_back({ muchie.v, muchie.w });
    }

    // dijkstra pt fiec nod sursa
    for (int s = 0; s < V; ++s) {
        vector<int> dist(V, INF);
        dist[s] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, s });

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (const auto& muchie : adj[u]) {
                int v = muchie.first;
                int w = muchie.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({ dist[v], v });
                }
            }
        }

        // afisam
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INF) {
                fout << "INF ";
            }
            else {
                int new_dist = dist[i] + h[i] - h[s];
                fout << new_dist << " ";
            }
        }
        fout << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}