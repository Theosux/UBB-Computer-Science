#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("in.txt");				// fisier primul ex
ifstream fin2("in2.txt");			// fisier al doilea ex

// Declarari primul ex:

int n;								// nr noduri
int nrMuchii = 0;					// nr muchii
int MatriceA[100][100];				// matrice - matricea de adiacenta
vector<int> ListaA[100];			// array de vectori - lista adiacenta
int MatriceI[100][100];				// matrice - matricea de incidenta
vector<int> ListaA2[100];			// array de vectori - a doua lista de adiacenta
int MatriceA2[100][100];			// matrice - a doua matrice de adiacenta

// Declarari al doilea ex:

int matriceDist[100][100];			// matrice - matricea de distanta

// Functii ex 1:

void GenerareMatriceA()
{
	fin >> n;
	int a, b;

	while (fin >> a >> b)
	{
		MatriceA[a][b] = 1;
		MatriceA[b][a] = 1;
	}

	cout << "Matrice de adiacenta:" << endl;			// Afisarea
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << MatriceA[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void GenerareMatriceA2()
{
	fin2 >> n;
	int a, b;

	while (fin2 >> a >> b)
	{
		MatriceA[a][b] = 1;
		MatriceA[b][a] = 1;
	}

	cout << "Matrice de adiacenta:" << endl;			// Afisarea
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << MatriceA[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void MatriceToListaA()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			if (MatriceA[i][j] == 1)
			{
				ListaA[i].push_back(j);
			}
		}
	cout << "Lista de adiacenta:" << endl;				// Afisarea
	for (int i = 1; i <= n; i++)
	{
		cout << "N " << i << ": ";
		for (int j : ListaA[i])
		{
			cout << j<< " ";
		}
		cout << endl;
	}
	cout << endl;
}

void ListaAToMatriceI()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j : ListaA[i])
		{
			if (i < j)									// cand gasim un vecin aceasta actioneaza ca un vector de frecventa
			{
				nrMuchii++;
				MatriceI[i][nrMuchii] = 1;
				MatriceI[j][nrMuchii] = 1;
			}
		}
	}

	cout << "Matrice incidenta: " << endl;				// Afisarea
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= nrMuchii; j++)
		{
			cout << MatriceI[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void MatriceIToListaA()
{
	for (int j = 1; j <= nrMuchii; j++)
	{
		int x = 0;
		int y = 0;

		for (int i = 1; i <= n; i++)
		{
			if (MatriceI[i][j] == 1)
			{
				if (x == 0)
				{
					x = i;								// Primul nod gasit
				}
				else
				{
					y = i;								// Al doilea
				}
			}
		}
		if (x != 0 && y != 0)
		{
			ListaA2[x].push_back(y);
			ListaA2[y].push_back(x);
		}
	}
	cout << "Lista de adiacenta: " << endl;				// Afisarea
	for (int i = 1; i <= n; i++)
	{
		cout << "N " << i << ": ";
		for (int j : ListaA2[i])
		{
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void ListaAToMatriceA()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j : ListaA2[i])
		{
			MatriceA2[i][j] = 1;
		}
	}

	cout << "Matrice de adiacenta:" << endl;			// Afisarea
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << MatriceA2[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}



// Functii ex 2:

void DetNoduriIzolate()
{
	for (int i = 1; i <= n; i++)
	{
		int ok = 1;
		for (int j = 1; j <= n; j++)
		{
			if (MatriceA[i][j] == 1)
			{
				ok = 0;
			}
		}
		if (ok == 1)							// Am gasit un nod izolat
		{
			cout << "Nodul " << i << " este izolat." << endl;
		}
	}
}

void DetGrafRegulat()
{
	int cnt = -1;
	int ok = 1;
	for (int i = 1; i <= n; i++)
	{
		if (ok == 1)
		{
			int cnt2 = 0;
			for (int j = 1; j <= n; j++)
			{
				if (MatriceA[i][j] == 1)
				{
					cnt2++;
				}
			}
			if (cnt == -1)							// Am gasit un nod izolat
			{
				cnt = cnt2;
			}
			else if (cnt != cnt2)
			{
				cout << "Graful nu este regulat!" << endl;
				ok = 0;
			}
		}

	}
	if (ok == 1)
	{
		cout << "Graful este regulat!" << endl;
	}
}

void DetMatriceDistante()
{
	int INF = 999999;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j)
			{
				matriceDist[i][j] = 0;							// Distanta la el insusi e 0
			}
			else if (MatriceA[i][j] == 1)
			{
				matriceDist[i][j] = 1;							// Muchie directa
			}
			else
			{
				matriceDist[i][j] = INF;						// Nu exista 
			}
		}
	}

	//Algoritmul Roy-Floyd
	for (int k = 1; k <= n; k++) 
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				
				if (matriceDist[i][k] != INF && matriceDist[k][j] != INF)
				{
					
					if (matriceDist[i][j] > matriceDist[i][k] + matriceDist[k][j])
					{
						matriceDist[i][j] = matriceDist[i][k] + matriceDist[k][j];
					}
				}
			}
		}
	}

	cout << "Matricea distantelor:" << endl;				// Afisarea
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (matriceDist[i][j] == INF)
			{
				cout << "INF ";
			}
			else
			{
				cout << matriceDist[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void DetGrafConex()
{
	int v[100] = { 0 };							// Vector de parcurgere
	int q[100];									// queue - bfs
	int st = 0, dr = 0;							

	
	q[0] = 1;
	v[1] = 1;
	int noduriVizitate = 1;						// contor

	while (st <= dr)
	{
		int curent = q[st]; 
		st++;

		// Vecinii:
		for (int i = 1; i <= n; i++)
		{
			
			if (MatriceA[curent][i] == 1 && v[i] == 0)
			{
				v[i] = 1;       
				dr++;                 
				q[dr] = i;
				noduriVizitate++;				// inc la nr de noduri atinse
			}
		}
	}

	if (noduriVizitate == n)
	{
		cout << "Graful e conex." << endl;
	}
	else
	{
		cout << "Graful nu e conex." << endl;
	}
}

int main() 
{
	int cmd = 0;
	cout << "Alege exercitiul: ";
	cin >> cmd;
	cout << endl;
	if (cmd == 1)
	{
		GenerareMatriceA();
		MatriceToListaA();
		ListaAToMatriceI();
		MatriceIToListaA();
		ListaAToMatriceA();
		return 0;
	}
	if (cmd == 2)
	{
		GenerareMatriceA2();
		DetNoduriIzolate();
		DetGrafRegulat();
		DetMatriceDistante();
		DetGrafConex();
		return 0;
	}
	else
	{
		cout << "Programul s-a oprit.";
		return 0;
	}
	

}
