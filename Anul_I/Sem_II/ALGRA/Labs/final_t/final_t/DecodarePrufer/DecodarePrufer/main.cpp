#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3){
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int M;
    if (!(fin >> M)) {
        return 0;
    }
    // Numarul de noduri =lungimea sirului + 1
    int N = M + 1;

    vector<int> prufer(M);
    vector<int> frecv(N, 0);

    // Citim secventa si numaram de cate ori apare fiecare nod
    for (int i = 0; i < M; ++i) {
        fin >> prufer[i];
        frecv[prufer[i]]++;
    }

    // Vectorul final de tati. Il initializam tot cu -1.
    vector<int> tata(N, -1);
    int ptr = 0;

    // Cautam prima frunza (primul nod cu frecventa 0)
    while (ptr < N && frecv[ptr] > 0) {
        ptr++;
    }
    int frunza_curenta = ptr;

    // Reconstruim arborele pas cu pas
    for (int i = 0; i < M; ++i) {
        int parinte = prufer[i];

        // Conectam frunza la parintele ei din secventa
        tata[frunza_curenta] = parinte;

        // Parintele si-a primit un copil, deci scadem asteptarea
        frecv[parinte]--;

         //daca parintele nu mai asteapta copii, devine el instantaneu frunza
        if (frecv[parinte] == 0 && parinte < ptr) {
            frunza_curenta = parinte;
        }
        else {
            // Altfel, inaintam pointerul  pentru a gasi urmatoarea frunza
            ptr++;
            while (ptr < N && frecv[ptr] > 0) {
                ptr++;
            }
            frunza_curenta = ptr;
        }
    }
    fout << N << "\n";
    if (!tata.empty()) {
        fout << tata[0];
        for (int i = 1; i < N; ++i) {
            fout << " " << tata[i];
        }
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}