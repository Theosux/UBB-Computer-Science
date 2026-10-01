#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int main(int argc, char* argv[])
{	
	if (argc != 3) {
		cerr << "Introduceti fisier intrare fisier iesire.\n";
		return 1;
	}
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	if (!fin.is_open() || !fout.is_open()) {
		cerr << "Eroare deschidere fisier.\n";
		return 1;
	}

	int V, E, S;									// varfurii, arce, s = nodul sursa

	if (!(fin >> V >> E >> S)) {
		return 0;									// in cazul unui fisier gol
	}

	vector<vector<pair<int, int>>> adj(V);			// lista de adiacenta - adj[nod sursa] = {nod destinatie, cost}

	for (int i = 0; i < E; i++) {
		int x, y, z;
		fin >> x >> y >> z;
		adj[x].push_back({ y,z });
	}

	vector<int> dist(V, INF);						// vector initial de dist (initial e infinit peste tot)
	dist[S] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, S });

	while (!pq.empty()) {
		int d = pq.top().first;						// distanta de la S pana la u
		int u = pq.top().second;					// nodul u
		pq.pop();

		if (d > dist[u]) continue;

		for (auto& muchie : adj[u]) {
			int v = muchie.first;
			int w = muchie.second;

			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.push({ dist[v], v });			// introducem noul drum cel mai scurt
			}

		}

	}

	// Afisare:
	for (int i = 0; i < V; i++) {
		if (dist[i] == INF) {
			fout << "INF ";
		}
		else {
			fout << dist[i] << ' ';
		}
	}

	fin.close();
	fout.close();
	return 0;
}

