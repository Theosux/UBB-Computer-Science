#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int M;
    if (!(fin >> M)) return 0;

    int N = M + 1;
    vector<int> seq(M);
    vector<int> degree(N, 0);

    for (int i = 0; i < M; ++i) {
        fin >> seq[i];
        degree[seq[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; ++i) {
        if (degree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> parent(N, -1);
    for (int i = 0; i < M; ++i) {
        int u = pq.top();
        pq.pop();
        
        int p = seq[i];
        parent[u] = p;
        
        degree[p]--;
        if (degree[p] == 0) {
            pq.push(p);
        }
    }

    fout << N << "\n";
    for (int i = 0; i < N; ++i) {
        fout << parent[i] << (i + 1 == N ? "" : " ");
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}
