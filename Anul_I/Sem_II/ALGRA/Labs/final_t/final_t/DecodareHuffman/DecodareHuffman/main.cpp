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
    int N;
    if (!(fin >> N)) return 0;
    //coada {frecventa,{ascii_minim,index_nod}
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    vector<int> st, dr, min_ascii;//st[i],dr[i] indicii copilor,min_ascii cod minim ascii din subarbore
    vector<char> info;//tine caracteru

    int n = 0;
    for (int i = 0; i < N; ++i) {
        fin >> ws; char ch = fin.get(); int fr; fin >> fr;
        info.push_back(ch); st.push_back(-1); dr.push_back(-1); min_ascii.push_back((int)ch);
        pq.push({ fr, {(int)ch, n++} });
    }
    // Reconstructie arbore
    while (pq.size() > 1) {
        auto stanga = pq.top(); pq.pop();
        auto dreapta = pq.top(); pq.pop();

        info.push_back('$');
        st.push_back(stanga.second.second);
        dr.push_back(dreapta.second.second);

        int m_ascii = min(stanga.second.first, dreapta.second.first);
        min_ascii.push_back(m_ascii);

        pq.push({ stanga.first + dreapta.first, {m_ascii, n++} });
    }
    int radacina = pq.top().second.second;

    string textCodificat;
    fin >> textCodificat;

    // Decodificare linie
    int curent = radacina;
    for (char bit : textCodificat) {
        curent = (bit == '0') ? st[curent] : dr[curent];
        if (st[curent] == -1 && dr[curent] == -1) {
            fout << info[curent];
            curent = radacina;
        }
    }
    fout << "\n";

    return 0;
}