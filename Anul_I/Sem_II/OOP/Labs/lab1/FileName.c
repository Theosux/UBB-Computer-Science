#include <stdio.h>

int main()
{
	int nr;
	double numar, suma=0;
	printf("Introduceti numarul de elemente:");
	scanf_s("%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		printf("Introduceti elementul %d:", i+1);
		scanf_s("%lf", &numar);
		suma += numar;
	}

	printf("Suma celor %d numere este: %.2f\n", nr, suma);
	return 0;
}