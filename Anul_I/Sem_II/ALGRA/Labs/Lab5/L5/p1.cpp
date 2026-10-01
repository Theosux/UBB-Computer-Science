//O(V*E^2)
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	// verif argumente fisiere input si output
	if (argc != 3) {
		cerr << "Eroare lipsa fisiere input si output. Trebuie 2 argumente\n";
		return 1;
	}

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	if (!fin.is_open() || !fout.is_open()) {
		cerr << "Eroare deschideer fisiere.\n";
		return 1;
	}
	int V, E;
	if (!(fin >> V >> E)) {
		return 0;
	}
	//creem capacitate care actioneaza ca un graf rezidual, stocand capacitatea disponibila pt fiecare arc
	vector<vector<int>> capacitate(V, vector<int>(V, 0));
	//adj memoreaza lisa de adiacenta
	vector<vector<int>> adj(V);

	for (int i = 0; i < E; i++) {
		int u, v, c;
		fin >> u >> v >> c;

		// evitam duplicarea muchiilor
		if (capacitate[u][v] == 0 && capacitate[v][u] == 0) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		capacitate[u][v] += c;
	}

	int sursa = 0;
	int sink = V - 1;		// destinatie
	int flux = 0;			//maxim

	// reconstruire drum BFS
	vector<int> parent(V);

	// bucla principala Edmonds-Karp
	while (true) {
		// resetam parintii la -1 pt a parcurge bfs din nou
		fill(parent.begin(), parent.end(), -1);

		queue<int> q;
		q.push(sursa);
		parent[sursa] = sursa;	// sursa e vizitata

		// bfs pt a gasi cel mai scurt drum de crestere
		while (!q.empty() && parent[sink] == -1) {
			int curr = q.front();
			q.pop();

			for (int next : adj[curr]) {
				// *daca next e nevizitat si avem capacitate reziduala pozitiva spre el
				if (parent[next] == -1 && capacitate[curr][next] > 0) {
					parent[next] = curr;
					q.push(next);
				}
			}
		}

		// daca nu s-a gasit niciun drum spre destinatie, avem fluxul maxim
		if (parent[sink] == -1) {
			break;
		}
		// refacem drumul de la destinatie la sursa
		// det fluxul maxim ce poate fi trimis pe drumul curent (capacitatea reziduala minima)
		int drum_flux = 9999; // init cu 'inf'
		for (int v = sink; v != sursa; v = parent[v]) {
			int u = parent[v];
			drum_flux = min(drum_flux, capacitate[u][v]);
		}

		// actualizam cap in graf rezidual:
		// scadem pe arcul direct si adunam pe cel invers
		for (int v = sink; v != sursa; v = parent[v]) {
			int u = parent[v];
			capacitate[u][v] -= drum_flux;
			capacitate[v][u] += drum_flux; // consumam din resursa si marim muchia inversa
		}

		flux += drum_flux;
	}

	fout << flux << "\n";

	fin.close();
	fout.close();

	return 0;

}
