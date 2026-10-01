#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
struct Muchie
{
	int u, v, w;
};
bool comparaMuchie(const Muchie& a, const Muchie& b)
{
	return a.w < b.w;
};
vector<int>tata;
int gaseste(int x)
{
	if (tata[x] == x)return x;
	return tata[x] = gaseste(tata[x]);
}
int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		return 1;
	}
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	int V, E;
	vector<Muchie>muchii;
	fin >> V >> E;
	tata.resize(V);
	muchii.resize(E);
	for (int i = 0; i < E; i++)
	{
		fin >> muchii[i].u >> muchii[i].v >> muchii[i].w;
	}
	for (int i = 0; i < V; i++)
		tata[i] = i;
	vector<pair<int, int>>arbore_cost_minim;
	int cost_total = 0;
	sort(muchii.begin(), muchii.end(), comparaMuchie);
	for (int i = 0; i < E; i++)
	{
		int tata_x = gaseste(muchii[i].u);
		int tata_y = gaseste(muchii[i].v);
		if (tata_x != tata_y)
		{
			tata[tata_y] = tata_x;
			cost_total += muchii[i].w;
			arbore_cost_minim.push_back({ muchii[i].u,muchii[i].v });
		}
		if (arbore_cost_minim.size() == V - 1)break;
	}
	sort(arbore_cost_minim.begin(), arbore_cost_minim.end());
	fout << cost_total << " " << "\n" << arbore_cost_minim.size() << endl;
	for (int i = 0; i < arbore_cost_minim.size(); i++)
	{
		fout << arbore_cost_minim[i].first << " " << arbore_cost_minim[i].second << "\n";
	}

	return 0;
	}