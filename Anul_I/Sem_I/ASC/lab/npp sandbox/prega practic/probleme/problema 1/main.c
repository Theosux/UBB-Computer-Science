//Se da un numar a reprezentat pe 32 biti fara semn.
//Se cere sa se afiseze reprezentarea in baza 16 a lui a,
//precum si rezultatul permutarilor circulare ale cifrelor sale.

#include <stdio.h>

int modul1(int n, char numar16[]);

void modul2(char numar16[]);

int main()
{
    int n, len;
    char rezultat[9];
    printf("Introdu numarul n: ");
    scanf("%u", &n);
    
    len = modul1(n, rezultat);
    printf("Numarul n in baza 16 este %s, iar permutarile sale sunt: \n", rezultat);
    
    for (int i = 1; i <= len; i++)
    {
        modul2(rezultat);
        printf("%u: %s\n", i, rezultat);
    }
    
    return 0;
}