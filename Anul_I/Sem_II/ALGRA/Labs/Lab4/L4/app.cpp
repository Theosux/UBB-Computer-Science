#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

//nod din arbore Huffman
struct HuffmanNode {
	int freq;
	unsigned char min_char; // cel mai mic cod ascii
	unsigned char ch;
	bool is_leaf;
	HuffmanNode* left;
	HuffmanNode* right;

	//constructor frunza
	HuffmanNode(unsigned char c, int f) : ch(c), min_char(c), freq(f), is_leaf(true), left(nullptr), right(nullptr) {}

	//constructor pentru un nod intern
	HuffmanNode(HuffmanNode* l, HuffmanNode* r) : is_leaf(false), left(l), right(r) {
		freq = l->freq + r->freq;
		min_char = min(l->min_char, r->min_char); //cmm ascii
	}
};

//regula de comparare
struct CompareNode {
	bool operator()(HuffmanNode* const& a, HuffmanNode* const& b) {
		if (a->freq == b->freq) {
			// daca frecv sunt egale cel cu min_char mai mic
			return a->min_char > b->min_char;
		}
		return a->freq > b->freq;
	}
};

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cerr << "Trebuie introduse 3 argumente(fisier intrare si iesire, nr problemei)\n";
		return 1;
	}

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	if (!fin.is_open() || !fout.is_open()) {
		cerr << "Eroare deschidere fisiere\n";
		return 1;
	}
	int nr = stoi(argv[3]);




	// --- PROBLEMA 1 ---

	if (nr == 1) {
		int n;
		fin >> n;

		//vector parinte
		vector<int> parent(n);

		//children cnt - contor de copii al fiecarui nod
		vector<int> children_cnt(n, 0);

		//citire
		for (int i = 0; i < n; i++) {
			fin >> parent[i];
			if (parent[i] != -1) {
				children_cnt[parent[i]]++;
			}
		}

		vector<int> prufer;
		prufer.reserve(n - 1); // *


		//alg de codare
		int p = 0;

		while (p < n && children_cnt[p] > 0) {
			p++;
		}

		int leaf = p;									//frunza curenta

		for (int i = 0; i < n - 1; i++) {
			int pr = parent[leaf];						//parintele frunzei curente
			prufer.push_back(pr);

			children_cnt[pr]--;

			//daca parintele devine acum frunza
			if (children_cnt[pr] == 0 && pr < p) {
				leaf = pr;								//trecem la parinte
			}
			else {
				p++;

				//se face selectia pentru noua frunza
				while (p < n && children_cnt[p] > 0) {
					p++;
				}
				leaf = p;
			}
		}

		fout << prufer.size() << "\n";
		for (int i = 0; i < prufer.size(); i++) {
			fout << prufer[i] << " ";
		}
		fin.close();
		fout.close();

		return 0;
	}



	// --- PROBLEMA 2 ---

	if (nr == 2) {
		int m;
		fin >> m;
		int n = m + 1; //nr de noduri

		vector<int> prufer(m);
		vector<int> children_cnt(n, 0);
		for (int i = 0; i < m; i++) {
			fin >> prufer[i];
			children_cnt[prufer[i]]++; //fiec aparitie inseamna copil++
		}

		vector<int> parent(n, -1);

		//Alg decodare
		int p = 0;

		while (p < n && children_cnt[p] > 0) {
			p++;
		}

		int leaf = p;	//primul nod care nu e in prufer

		for (int i = 0; i < m; i++) {
			int pr = prufer[i];     //parintele frunzei este exact elem din cod
			parent[leaf] = pr;      //refacem legatura

			children_cnt[pr]--;     //contorul de copii scade o data ce parintele isi "gaseste copilul"

			//verificam daca parintele devine frunza
			if (children_cnt[pr] == 0 && pr < p) {
				leaf = pr;
			}
			else {
				p++;

				//altfel cautam urmatoarea frunza
				while (p < n && children_cnt[p] > 0) {
					p++;
				}
				leaf = p;
			}
		}

		fout << n << "\n";
		for (int i = 0; i < n; i++) {
			fout << parent[i] << " ";
		}
		fin.close();
		fout.close();

		return 0;
	}




	// --- PROBLEMA 3 ---

	if (nr == 3) {
		string text = "";
		char c;
		while (fin.get(c)) {
			text += c;
		}

		if (text.empty()) {
			fout << "0\n\n";
			return 0;
		}

		int freq[256] = { 0 };
		for (char ch : text) {
			freq[(unsigned char)ch]++;
		}

		int unique_chars = 0;
		for (int i = 0; i < 256; i++) {
			if (freq[i] > 0) {
				unique_chars++;
			}
		}

		fout << unique_chars << "\n";

		//constr arbore cu priority_q
		priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;

		for (int i = 0; i < 256; i++) {
			if (freq[i] > 0) {
				//ordine lexicografica
				fout << (char)i << " " << freq[i] << "\n";
				//adaugam frunze
				pq.push(new HuffmanNode((unsigned char)i, freq[i]));
			}
		}

		//caz special, un singur tip de ch
		if (unique_chars == 1) {
			for (char ch : text) {
				fout << "0";
			}
			fout << "\n";
			fin.close();
			fout.close();
			return 0;
		}

		//arborele huffman
		while (pq.size() > 1) {
			//cele mai mici 2 noduri
			HuffmanNode* left = pq.top(); pq.pop();
			HuffmanNode* right = pq.top(); pq.pop();

			//parintele
			HuffmanNode* parent = new HuffmanNode(left, right);
			pq.push(parent);
		}
		//radacina
		HuffmanNode* root = pq.top();

		string huffman_codes[256];

		vector<pair<HuffmanNode*, string>> stack;
		stack.push_back({ root, "" });

		while (!stack.empty()) {
			pair<HuffmanNode*, string> current = stack.back();
			stack.pop_back();

			HuffmanNode* node = current.first;
			string code = current.second;

			if (node->is_leaf) {
				huffman_codes[node->ch] = code;
			}
			else {
				//stanga 0, dreapta 1
				stack.push_back({ node->right, code + "1" });
				stack.push_back({ node->left, code + "0" });
			}
		}

		//afisare
		for (char ch : text) {
			fout << huffman_codes[(unsigned char)ch];
		}

		fout << "\n";
		fin.close();
		fout.close();

		return 0;
	}




	// --- PROBLEMA 4 ---

	if (nr == 4) {
		int n;
		fin >> n;

		char chr;	// dummy uri
		fin.get(chr);

		//asemanator 3
		priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;

		for (int i = 0; i < n; i++) {
			char ch;
			fin.get(ch);
			fin.get(chr);

			int fr;
			fin >> fr;
			fin.get(chr);

			//frunza
			pq.push(new HuffmanNode((unsigned char)ch, fr));
		}

		string encoded_text;
		fin >> encoded_text; //binar

		//caz particular: un singur char
		if (n == 1) {
			char single_char = pq.top()->ch;
			//repetat
			for (size_t i = 0; i < encoded_text.length(); i++) {
				fout << single_char;
			}
			fout << "\n";
			fin.close();
			fout.close();
			return 0;
		}

		//reconsituire arbore
		while (pq.size() > 1) {
			HuffmanNode* left = pq.top(); pq.pop();
			HuffmanNode* right = pq.top(); pq.pop();

			HuffmanNode* parent = new HuffmanNode(left, right);
			pq.push(parent);
		}

		//nodul ramas - radacina
		HuffmanNode* root = pq.top();

		//decodare
		HuffmanNode* current = root;

		for (char bit : encoded_text) {
			//0 - stanga, 1 - dreapta
			if (bit == '0') {
				current = current->left;
			}
			else {
				current = current->right;
			}

			//frunza - caracter decodat
			if (current->is_leaf) {
				fout << current->ch; //caracter in fisier
				current = root;      //radacina - urm bit
			}
		}

		fout << "\n";
		fin.close();
		fout.close();

		return 0;
	}




	// --- PROBLEMA 5 ---

	if (nr == 5) {
		int V, E;
		fin >> V >> E;

		//muchie
		struct Edge {
			int u, v, weight;
			//sortare "<"
			bool operator<(const Edge& other) const {
				if (weight != other.weight) return weight < other.weight;
				if (u != other.u) return u < other.u;
				return v < other.v;
			}
		};

		vector<Edge> edges(E);
		for (int i = 0; i < E; i++) {
			fin >> edges[i].u >> edges[i].v >> edges[i].weight;

			// u < v
			if (edges[i].u > edges[i].v) {
				swap(edges[i].u, edges[i].v);
			}
		}

		//sortam dupa cost
		sort(edges.begin(), edges.end());

		//dsu - cicluri
		struct DSU {
			vector<int> parent;
			vector<int> rank;

			DSU(int n) {
				parent.resize(n);
				rank.assign(n, 0);
				for (int i = 0; i < n; i++) parent[i] = i;
			}

			int find(int i) {
				if (parent[i] == i)
					return i;
				return parent[i] = find(parent[i]);
			}

			bool unite(int i, int j) {
				int root_i = find(i);
				int root_j = find(j);

				if (root_i != root_j) {
					if (rank[root_i] < rank[root_j]) {
						parent[root_i] = root_j;
					}
					else if (rank[root_i] > rank[root_j]) {
						parent[root_j] = root_i;
					}
					else {
						parent[root_j] = root_i;
						rank[root_i]++;
					}
					return true; //unire
				}
				return false;
			}
		};

		DSU dsu(V);
		int total_cost = 0;
		vector<Edge> mst_edges;
		mst_edges.reserve(V - 1);

		//parcurgere dupa cost
		for (int i = 0; i < E; i++) {
			//fara ciclu
			if (dsu.unite(edges[i].u, edges[i].v)) {
				total_cost += edges[i].weight; //adunam
				mst_edges.push_back(edges[i]); //adaugam arbore
			}

			//oprim la V-1 muchii
			if (mst_edges.size() == V - 1) {
				break;
			}
		}

		//sortam rezultatul
		sort(mst_edges.begin(), mst_edges.end(), [](const Edge& a, const Edge& b) {
			if (a.u != b.u) return a.u < b.u;
			return a.v < b.v;
			});

		//afisare
		fout << total_cost << "\n";
		fout << mst_edges.size() << "\n";
		for (const auto& edge : mst_edges) {
			fout << edge.u << " " << edge.v << "\n";
		}

		fin.close();
		fout.close();

		return 0;
	}
	cerr << "al treilea argument poate fi 1-5\n";
	return 1;
}