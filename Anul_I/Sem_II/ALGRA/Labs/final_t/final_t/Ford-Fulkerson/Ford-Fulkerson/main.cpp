#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
vector<bool>vizitat;
int cap[1005][1005];
vector<vector<int>>dij;
int dfs(int u, int t, int flux_minim)
{
	if (u == t)
		return flux_minim;
	vizitat[u] = true;
	for (int v : dij[u])
	{
		if (cap[u][v] > 0 && !vizitat[v])
		{
			int flux_rec = dfs(v, t, min(cap[u][v], flux_minim));
			if (flux_rec > 0)
			{
				cap[u][v] -= flux_rec;
				cap[v][u] += flux_rec;
				return flux_rec;

			}
		}
	}
	return 0;

}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		return 1;
	}
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	int V, E, x, y, z;
	fin >> V >> E;
	vizitat.resize(V);
	dij.resize(V);
	for (int i = 0; i < E; i++)
	{
		fin >> x >> y >> z;
		dij[x].push_back(y);
		dij[y].push_back(x);
		cap[x][y] = z;

	}
	int flux_maxim = 0;
	while (true)
	{
		fill(vizitat.begin(), vizitat.end(), false);
		int flux_minim = dfs(0, V - 1, 2e9);
		if (flux_minim == 0)break;
		flux_maxim += flux_minim;
	}
	fout << flux_maxim;

	return 0;
}