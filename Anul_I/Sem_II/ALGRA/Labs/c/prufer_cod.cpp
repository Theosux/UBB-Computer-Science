#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int N;
    if (!(fin >> N)) return 0;

    vector<int> parent(N);
    vector<int> degree(N, 0);
    int root = -1;

    for (int i = 0; i < N; ++i) {
        fin >> parent[i];
        if (parent[i] != -1) {
            degree[parent[i]]++;
        } else {
            root = i;
        }
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; ++i) {
        if (degree[i] == 0 && i != root) {
            pq.push(i);
        }
    }

    vector<int> prufer;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        
        int p = parent[u];
        prufer.push_back(p);
        
        degree[p]--;
        if (degree[p] == 0 && p != root) {
            pq.push(p);
        }
    }

    fout << prufer.size() << "\n";
    for (size_t i = 0; i < prufer.size(); ++i) {
        fout << prufer[i] << (i + 1 == prufer.size() ? "" : " ");
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}
