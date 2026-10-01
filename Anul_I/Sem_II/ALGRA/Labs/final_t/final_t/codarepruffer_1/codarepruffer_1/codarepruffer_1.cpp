#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int N;
    if (!(fin >> N)) return 0;

    vector<int> tata(N);
    vector<int> frecv(N, 0);

    // citim vectorul de tati si numaram copiii fiecaruia
    for (int i = 0; i < N; ++i) {
        fin >> tata[i];
        if (tata[i] != -1) {
            frecv[tata[i]]++;
        }
    }

    vector<int> cod_prufer;
    int ptr = 0;

    // prima frunza (nod cu 0 copii)
    while (ptr < N && frecv[ptr] > 0) {
        ptr++;
    }
    int frunza_curenta = ptr;

    // generam secv prufer de n-1 
    for (int i = 0; i < N - 1; ++i) {
        int parinte = tata[frunza_curenta];
        cod_prufer.push_back(parinte);

        // elim frunza,parintele isi pierde fiul
        if (parinte != -1) {
            frecv[parinte]--;
        }

          //daca parintele e fara copii devine el frunza
        if (parinte != -1 && frecv[parinte] == 0 && parinte < ptr) {
            frunza_curenta = parinte;
        }
        else {
            // Altfel,cautam la dreapta
            ptr++;
            while (ptr < N && frecv[ptr] > 0) {
                ptr++;
            }
            frunza_curenta = ptr;
        }
    }

    fout << cod_prufer.size() << "\n";
    for (int i = 0; i < cod_prufer.size(); ++i) {
        fout << cod_prufer[i];

        if (i < cod_prufer.size() - 1) {
            fout << " ";
        }
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}