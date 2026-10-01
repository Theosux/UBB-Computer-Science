#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;


void DFS_VISIT(int u, const vector<vector<int>>& a, vector<bool>& vizitat) {
	// vizitat
	vizitat[u] = true;
	cout << "  Nod descoperit: " << u << "\n";

	// vecinii
	for (int v : a[u]) {
		// recursiv mergem la vecinii nevizitati
		if (!vizitat[v]) {
			DFS_VISIT(v, a, vizitat);
		}
	}
}


int main() {
	int cmd = 0;
	cout << "Exercitiile:\n\n" << "1.Algoritmul lui Moore\n" << "2.Inchiderea transitiva a unui graf orientat\n" << "3.Labirinturi\n" << "4.Varfuri BFS\n" << "5.Varfuri DFS_VISIT";
	cout << "\n\nAlege exercitiul:";
	cin >> cmd;
	cout << '\n';
	if (cmd == 1) {
		ifstream fin("graf.txt");
		int n;
		fin >> n;
		//lista de adiacenta
		vector<vector<int>> a(n + 1);
		int x, y;
		while (fin >> x >> y) {
			a[x].push_back(y);
		}
		fin.close();


		int nodS, nodD;
		cout << "Introdu nodul sursa:";
		cin >> nodS;
		cout << '\n';
		cout << "Introdu nodul destinatie:";
		cin >> nodD;
		cout << '\n';

		// vectorii algoritmului Moore
		vector<int> l(n + 1, -1);	// lungime
		vector<int> p(n + 1, 0);	// parinte
		queue<int> Q;

		l[nodS] = 0;
		Q.push(nodS);

		// bfs
		while (!Q.empty()) {
			int x = Q.front();
			Q.pop();
			
			for (int y : a[x]) {
				if (l[y] == -1) {
					p[y] = x;           
					l[y] = l[x] + 1;    
					Q.push(y);          
				}
			}
		}

		if (l[nodD] == -1) {
			cout << "Nu exista drum de la " << nodS << " la" << nodD << ".\n";
		}
		else {
			cout << "Lungimea celui mai scurt drum este: " << l[nodD] << ".\n";


			// construim drumul
			vector<int> drum;
			int curent = nodD;

			while (curent != 0) {
				drum.push_back(curent);
				curent = p[curent];
			}

			reverse(drum.begin(), drum.end());

			// afisam drumul
			cout << "Drumul: ";
			for (int i = 0; i < drum.size(); i++) {
				cout << drum[i] << (i < drum.size() - 1 ? " -> " : "");
			}
			cout << "\n";

		}

		return 0;
	}
	if (cmd == 2) {
		ifstream fin("graf.txt");
		int n;
		fin >> n;

		// matrice de adiacenta
		int M[50][50] = { 0 };
		int x, y;
		for (int i = 1; i <= n; i++) {
			M[i][i] = 1;
		}
		while (fin >> x >> y) {
			M[x][y] = 1;
		}
		fin.close();

		cout << "Matrice de adiacenta: \n";
		for (int i = 0; i <= n; i++) {
			cout << i << ' ';
		}
		cout << '\n';
		for (int i = 1; i <= n; i++) {
			cout << i << ' ';
			for (int j = 1; j <= n; j++) {
				cout << M[i][j] << ' ';
			}
			cout << '\n';
		}
		// Floyd Warshall;
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					M[i][j] = M[i][j] || (M[i][k] && M[k][j]);
				}
			}
		}
		cout << "\n\n";
		cout << "Matrice de inchidere tranz: \n";
		for (int i = 0; i <= n; i++) {
			cout << i << ' ';
		}
		cout << '\n';
		for (int i = 1; i <= n; i++) {
			cout << i << ' ';
			for (int j = 1; j <= n; j++) {
				cout << M[i][j] << ' ';
			}
			cout << '\n';
		}

		return 0;
	}
	if (cmd == 3) {
		string FileName;
		cout << "Alege numele filei(1/2/3):\n";
		cout << "1.labirint_1\n";
		cout << "2.labirint_2\n";
		cout << "3.labirint_cuvinte\n\n";
		int cmd = 0;
		while (true) {
			cmd = 0;
			cin >> cmd;
			if (cmd == 1) {
				FileName = "labirint_1.txt";
				break;
			}
			if (cmd == 2) {
				FileName = "labirint_2.txt";
				break;
			}
			if (cmd == 3) {
				FileName = "labirint_cuvinte.txt";
				break;
			}
			cout << "Alege 1/2/3:";
		}
		cin.ignore();

		ifstream fin(FileName);
		if (!fin.is_open()) {
			cout << "Eroare, deschidere";
			return 0;
		}
		vector<string> labirint;
		string line;
		while (getline(fin, line)) {
			if (!line.empty() && line.back() == '\r') {
				line.pop_back();
			}
			if (line.length() > 0) {
				labirint.push_back(line);
			}
		}
		fin.close();

		int startR = -1, startC = -1, endR = -1, endC = -1;

		for (int i = 0; i < labirint.size(); i++) {
			for (int j = 0; j < labirint[i].size(); j++) {
				if (labirint[i][j] == 'S') {
					startR = i;
					startC = j;
				}
				if (labirint[i][j] == 'F') {
					endR = i;
					endC = j;
				}
			}
		}

		if (startR == -1) {
			for (int i = 0; i < labirint.size() && startR == -1; i++) {
				for (int j = 0; j < labirint[i].size(); j++) {
					if (labirint[i][j] == ' ') {
						startR = i;
						startC = j;
						break;
					}
				}
			}
			for (int i = labirint.size() - 1; i >= 0 && endR == -1; i--) {
				for (int j = 0; j < labirint[i].size(); j++) {
					if (labirint[i][j] == ' ') {
						endR = i;
						endC = j;
						break;
					}
				}
			}
		}
		if (startR == -1 || endR == -1) {
			cout << "Eroare, nu au fost gasite punctele de start si final.";
			return 0;
		}

		int rows = labirint.size();

		vector<vector<pair<int, int>>> parinte(rows);
		vector<vector<bool>> vizitat(rows);

		for (int i = 0; i < rows; i++) {
			parinte[i].resize(labirint[i].size(), { -1, -1 });
			vizitat[i].resize(labirint[i].size(), false);
		}

		queue<pair<int, int>> Q;
		Q.push({ startR, startC });
		vizitat[startR][startC] = true;

		// directii: sus jos stanga dreapta
		int dRow[] = { -1, 1, 0, 0 };
		int dCol[] = { 0, 0, -1, 1 };
		bool gasit = false;

		// BFS
		while (!Q.empty()) {
			pair<int, int> curent = Q.front();
			int r = curent.first;
			int c = curent.second;
			Q.pop();

			if (r == endR && c == endC) {
				gasit = true;
				break;
			}

			// vecini
			for (int i = 0; i < 4; i++) {
				int nr = r + dRow[i];
				int nc = c + dCol[i];

				// limite
				if (nr >= 0 && nr < rows && nc >= 0 && nc < labirint[nr].size()) {
					if (!vizitat[nr][nc] && labirint[nr][nc] != '1') {
						vizitat[nr][nc] = true;
						parinte[nr][nc] = { r, c };
						Q.push({ nr, nc });
					}
				}
			}
		}

		if (gasit) {
			cout << "\nSolutie gasita! traseu - '*'\n\n";
			int cr = endR, cc = endC;

			// 'backtracking'
			while (cr != startR || cc != startC) {
				if (labirint[cr][cc] != 'F' && labirint[cr][cc] != 'S') {
					labirint[cr][cc] = '*';
				}
				pair<int, int> p = parinte[cr][cc];
				cr = p.first;
				cc = p.second;
			}

			// afisare
			for (const string& labirint_line : labirint) {
				cout << labirint_line << "\n";
			}
		}
		else {
			cout << "\nNu a fost gasita solutie.\n";
		}
		return 0;
	}
	if (cmd == 4) {
		ifstream fin("graf.txt");
		
		int n;
		fin >> n;

		// lista de adiacenta
		vector<vector<int>> a(n + 1);
		int x, y;
		while (fin >> x >> y) {
			a[x].push_back(y);
			// a[y].push_back(x);      <- pt graf neorientat decomentam
		}
		fin.close();

		int nodS;
		cout << "Introdu nodul sursa:";
		cin >> nodS;
		cout << '\n';

		// vector distante
		vector<int> d(n + 1, -1);
		queue<int> Q;

		d[nodS] = 0;
		Q.push(nodS);

		cout << "Arborele bfs descoperit pornind din nodul " << nodS << ":\n";
		cout << "Nod: " << nodS << " ; distanta: " << d[nodS] << "\n";

		// bfs

		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();

			for (int v : a[u]) {
				if (d[v] == -1) {
					d[v] = d[u] + 1;
					Q.push(v);

					cout << "Nod: " << v << " ; distanta: " << d[v] << "\n";
				}
			}
		}

		return 0;
	}
	if (cmd == 5) {
		ifstream fin("graf.txt");

		int n;
		fin >> n;

		vector<vector<int>> a(n + 1);
		int x, y;
		while (fin >> x >> y) {
			a[x].push_back(y);
		}
		fin.close();

		//vectorii dfs
		vector<bool> vizitat(n + 1, false);

		cout <<	"\nPadurea DFS descoperita:\n";

		for (int u = 1; u <= n; u++) {
			if (!vizitat[u]) {
				cout << "\nArbore DFS nou (radacina " << u << "):\n";
				DFS_VISIT(u, a, vizitat);
			}
		}

		return 0;
	}
	else {
		return 0;
	}
	return 0;
}