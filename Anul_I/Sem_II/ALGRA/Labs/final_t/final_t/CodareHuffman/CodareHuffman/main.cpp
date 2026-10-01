#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    ifstream fin(argv[1]); ofstream fout(argv[2]);
    string text;
    if (!getline(fin, text) || text.empty()) return 0;
    map<char, int> frecv;
    for (char c : text) frecv[c]++;
     // Coada : {frecventa, {ASCII_minim, index_nod}}
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    vector<int> st, dr, min_ascii;//st,dr ->indici copii,min_ascii cel mai mic ocd ASCII
    vector<char> info;//tine caractere
    int n = 0;
    for (auto p : frecv) {
        info.push_back(p.first); st.push_back(-1); dr.push_back(-1); min_ascii.push_back((int)p.first);
        pq.push({ p.second, {(int)p.first, n++} });//introducem caracterele unice in coada
    }
    while (pq.size() > 1) {//constructie arbore
        auto stanga = pq.top(); pq.pop();//nod stang
        auto dreapta = pq.top(); pq.pop();//nod drept
        info.push_back('$');//cream nod parinte

        st.push_back(stanga.second.second);//setam copii noului nod(St,Dr)
        dr.push_back(dreapta.second.second);
        int m_ascii = min(stanga.second.first, dreapta.second.first);//calculam codul minim ascii
        min_ascii.push_back(m_ascii);

        // Suma frecventelor, noul ASCII minim, noul index
        pq.push({ stanga.first + dreapta.first, {m_ascii, n++} });
    }
    int radacina = pq.top().second.second;

    // Generam codurile cu o coada simpla
    map<char, string> coduri;
    queue<pair<int, string>> q_cod;
    q_cod.push({ radacina, "" });//pornimm cu o radacina goala

    while (!q_cod.empty()) {
        int nod = q_cod.front().first; string cod = q_cod.front().second; q_cod.pop();//scoatem nod
        if (st[nod] == -1 && dr[nod] == -1) coduri[info[nod]] = cod;//daca nodul este frunza(am format codul complet)
        else {//are copii
            if (st[nod] != -1) q_cod.push({ st[nod], cod + "0" });//adaugam la stanga 0
            if (dr[nod] != -1) q_cod.push({ dr[nod], cod + "1" });//la dreapta 1
        }
    }
    // Afisare alfabet
    fout << frecv.size() << "\n";
    for (auto p : frecv) fout << p.first << " " << p.second << "\n";

    // Afisare text codificat
    for (char c : text) fout << coduri[c];
    fout << "\n";

    return 0;
}