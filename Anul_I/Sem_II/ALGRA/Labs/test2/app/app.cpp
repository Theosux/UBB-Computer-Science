#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

int main() {
	int n;
	fin >> n;

	vector<int> s(n - 2);
	vector<int> frecv(n + 1, 0);

	//citim secv si calculam frecventa fiecarui nod
	for (int i = 0; i < n - 2; i++) {
		fin >> s[i];
		frecv[s[i]]++;
	}

	//reconstruirea arborelui
	for (int i = 0; i < n - 2; i++) {
		int nod_min = 1;
		while (frecv[nod_min] != 0) {
			nod_min++;
		}

		//adaugam si afisam muchia dintre cel mai mic nod disponibil si primul el din secv
		fout << nod_min << " " << s[i] << "\n";

		//folosim frunza
		frecv[nod_min] = -1;

		//scadem secventa
		frecv[s[i]]--;

	}

	// secventa este vida, cautam cele 2 noduri ramase nefolosite(frecv 0)
	vector<int> nod_r;
	for (int i = 1; i <= n; i++) {
		if (frecv[i] == 0) {
			nod_r.push_back(i);
		}
	}

	// ultimele 2
	fout << nod_r[0] << " " << nod_r[1] << "\n";

	fin.close();
	fout.close();
	return 0;

}