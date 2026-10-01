#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

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

void generateCodes(Node* root, string currentCode, map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->c] = currentCode;
        return;
    }
    generateCodes(root->left, currentCode + "0", codes);
    generateCodes(root->right, currentCode + "1", codes);
}

int main(int argc, char * argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    string text = "";
    char ch;
    map<char, int> freq;
    while (fin.get(ch)) {
        text += ch;
        freq[ch]++;
    }

    if (text.empty()) return 0;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    vector<pair<char, int>> alphabet;
    
    for (auto const& [c, f] : freq) {
        pq.push(new Node(c, f));
        alphabet.push_back({c, f});
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        pq.push(new Node(left, right));
    }

    Node* root = pq.top();
    map<char, string> codes;
    if (!root->left && !root->right) {
        codes[root->c] = "0";
    } else {
        generateCodes(root, "", codes);
    }

    fout << alphabet.size() << "\n";
    for (auto const& pair : alphabet) {
        fout << pair.first << " " << pair.second << "\n";
    }

    for (char c : text) {
        fout << codes[c];
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}
