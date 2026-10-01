#include <stdio.h>
#include <stdbool.h>

void determineRelativePrime(int n)
{
	/*
	Pre: n - integer (dar natural)
	Post: nr afisate sunt mai mici ca n
	Descriere: functia afiseaza numerele mai mici ca n care sunt relativ prime cu el, (exceptie) pentru n == 0 sau 1
	*/

	if (n == 0 || n == 1)
	{
		printf("Nu exista numere mai mici ca %d relativ prime cu el", n);
	}
	else if (n == 2)
	{
		printf("1");
	}
	else
	{
		for (int i = 2; i < n; i++)
		{
			if (cmmdcIsOne(n, i) == 1)
			{
				printf("%d ", i);
			}
		}
	}


}

int cmmdcIsOne(int a, int b)
{
	/*
	Pre: a, b - integer (naturale)
	Post: int, 1 - pentru nr relativ prime intre ele, altfel 0
	Descriere: Functia determina daca doua nr sunt relativ prime intre ele
	*/
	while (a != b)
	{
		if (a > b)
		{
			a = a - b;
		}
		else
		{
			b = b - a;
		}
	}
	if (a == 1)
	{
		return 1;
	}
	return 0;

}

void printPascalTriangle(int n)
{
	/*
	Pre: n - integer (numarul de linii)
	Post: afiseaza triunghiul lui Pascal pana la linia n
	Descriere: Tipareste combinarile C(m, k)
	*/
	for (int m = 1; m <= n; m++)
	{
		int c = 1;

		for (int k = 0; k <= m; k++)
		{
			printf("%d ", c);
			c = c * (m - k) / (k + 1);
		}
		printf("\n");
	}
}

int main()
{
	int cmd = 0;

	printf("1. Exercitiul 16.\n");
	printf("2. Exercitiul 6.\n");
	printf("Alege exercitiul:");

	scanf_s("%d", &cmd);
	if (cmd == 1)
	{
		while (true)
		{
			printf("1. Introdu un nou numar \n2. Iesire\n");

			int icmd = 0;

			printf("Introduceti comanda:");
			scanf_s("%d", &icmd);
			if (getchar() != '\n')
			{
				printf("Alege una dintre optiuni!\n");
			}

			if (icmd == 2)
			{
				break;
			}
			if (icmd == 1)
			{
				int n = 0;
				printf("Introduceti numarul:");
				scanf_s("%d", &n);

				determineRelativePrime(n);
				printf("\n");
			}

		}
	}
	if (cmd == 2)
	{
		while (true)
		{
			printf("1. Genereaza Triunghiul lui Pascal \n2. Iesire\n");

			int icmd = 0;

			printf("Introduceti comanda:");
			scanf_s("%d", &icmd);

			if (icmd == 2)
			{
				break;
			}
			if (icmd == 1)
			{
				int n = 0;
				printf("Introduceti n (numarul de linii):");
				scanf_s("%d", &n);

				printPascalTriangle(n);
				printf("\n");
			}
		}
	}
	if (cmd != 1 && cmd != 2)
	{
		printf("Programul s-a incheiat, te rog alege 1 sau 2");
	}

	return 0;
}