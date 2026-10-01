#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

struct Node {
    char c;
    int freq;
    int min_ascii;
    Node* left;
    Node* right;
    Node(char ch, int f) : c(ch), freq(f), min_ascii(ch), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : c(0), freq(l->freq + r->freq), left(l), right(r) {
        min_ascii = min(l->min_ascii, r->min_ascii);
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq != b->freq) return a->freq > b->freq;
        return a->min_ascii > b->min_ascii;
    }
};

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int N;
    if (!(fin >> N)) return 0;

    fin.get(); // consume newline
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    for (int i = 0; i < N; ++i) {
        char ch;
        fin.get(ch);
        char space;
        fin.get(space);
        int fr;
        fin >> fr;
        fin.get(); // consume newline
        pq.push(new Node(ch, fr));
    }

    string bit_string;
    fin >> bit_string;

    if (pq.empty()) return 0;
    
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        pq.push(new Node(left, right));
    }

    Node* root = pq.top();
    
    string decodedText = "";
    Node* current = root;
    
    if (!root->left && !root->right) {
        for(size_t i=0; i<bit_string.length(); ++i) {
            decodedText += root->c;
        }
    } else {
        for (char bit : bit_string) {
            if (bit == '0') current = current->left;
            else current = current->right;
            
            if (!current->left && !current->right) {
                decodedText += current->c;
                current = root;
            }
        }
    }

    fout << decodedText << "\n";

    fin.close();
    fout.close();
    return 0;
}
