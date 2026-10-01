#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int INF = 1e9;

struct Muchie {
	int u, v, w;
};

int main() {
	ifstream fin("input.in");
	ofstream fout("output.out");

	if (!fin.is_open() || !fout.is_open()) {
		cerr << "fisier!\n";
		return 1;
	}

	int n, m;
	if (!(fin >> n >> m)) return 0;

	vector<Muchie> muchii(m);				// retinem mai usor muchiile
	for (int i = 0; i < m; i++) {
		fin >> muchii[i].u >> muchii[i].v >> muchii[i].w;
	}	

	int s;
	fin >> s;

	// vectorul de dist (init cu INF)
	vector<int> dist(n + 1, INF);
	dist[s] = 0;

	// bellman - ford
	for (int i = 1; i <= n - 1; i++) {
		bool any_relaxed = false;
		for (const auto& muchie : muchii) {
			if (dist[muchie.u] != INF && dist[muchie.u] + muchie.w < dist[muchie.v]) {
				dist[muchie.v] = dist[muchie.u] + muchie.w;
				any_relaxed = true;
			}
		}
		// daca nu s-au efectuat
		if (!any_relaxed) break;
	}

	// ciclu negativ
	bool neg_cycle = false;
	for (const auto& muchie : muchii) {
		if (dist[muchie.u] != INF && dist[muchie.u] + muchie.w < dist[muchie.v]) {
			neg_cycle = true;
			break;
		}
	}

	if (neg_cycle) {
		fout << "Ciclu negativ\n";
	}
	else {
		for (int i = 1; i <= n; i++) {
			if (dist[i] == INF) {
				fout << "INF ";
			}
			else {
				fout << dist[i] << " ";
			}
		}
		fout << "\n";
	}


	fin.close();
	fout.close();

	return 0;
}