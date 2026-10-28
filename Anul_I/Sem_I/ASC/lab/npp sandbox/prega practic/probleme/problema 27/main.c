//Se citesc din fisierul numere.txt mai multe numere (pare si impare).
//Sa se creeze 2 siruri rezultat N si P astfel: N - doar numere impare si P - doar numere pare.
//Afisati cele 2 siruri rezultate pe ecran.

// 12 13 8 10 7 9
// : 12 8 10
// : 13 7 9
// dd 12, 13, 8, 10, 7, 9

#include <stdio.h>

void modul1(int s[], int N[]);
void modul2(int s[], int P[]);

int main()
{
    int s[100];
    int N[100]; // Sir de nr impare
    int P[100]; // Sir de nr pare
    FILE *fin = fopen("numere.txt", "r");
    if (!fin) return 1;
    fread(fin, "%s", &s);
    
    modul1(s, N);
    modul2(s, P);
    
    printf("Sirul de numere impare este: %s", N);
    printf("Sirul de numere pare este: %s", P);
    
    return 0;
}