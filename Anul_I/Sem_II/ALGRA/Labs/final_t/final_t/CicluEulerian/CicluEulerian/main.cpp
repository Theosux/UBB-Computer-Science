#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;
struct Edge {//structur id_muchie,catre cine merge
    int to;
    int id_muchie;
};


int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<Edge>> adj(V);//lista de adiacenta
    vector<bool> muchie_vizitata(E, false);//vector vizitat

    for (int i = 0; i < E; ++i) {//citim datele
        int u, v;
        fin >> u >> v;
        adj[u].push_back({ v, i });//i=id
        adj[v].push_back({ u, i });
    }

    stack<int> stiva;//stiva
    vector<int> circuit_final;//circuitul format
    stiva.push(0);//incepem din nodu 0 ;

    vector<int> pointer_muchie(V, 0);//a cata muchie am ramas
    while (!stiva.empty()) {
        int u = stiva.top();
        bool am_avansat = false;//variabila spune daca am gasit un drum liber

        while (pointer_muchie[u] < adj[u].size()) {
            Edge e = adj[u][pointer_muchie[u]];//extragem muchie
            pointer_muchie[u]++;//mutam pointer

            if (!muchie_vizitata[e.id_muchie]) {//daca nu este vizitata
                muchie_vizitata[e.id_muchie] = true; //setam ca fiind vizitat
                stiva.push(e.to);                    //ne mutam la urm nod
                am_avansat = true;//setam variabila
                break;
            }
        }

        if (!am_avansat) {
            circuit_final.push_back(u);//daca u este fundatura il adaugam in circuit
            stiva.pop();//scoatem din stiva
        }
    }

    if (!circuit_final.empty()) {//afisam
        fout << circuit_final[0];
        for (int i = 1; i < circuit_final.size(); ++i) {
            fout << " " << circuit_final[i];
        }
    }

    fin.close();
    fout.close();
    return 0;
}