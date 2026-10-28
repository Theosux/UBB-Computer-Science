// Se citesc mai multe siruri de caractere.
//Sa se determine daca primul apare ca subsecventa in fiecare din celelalte si sa se dea un mesaj corespunzator.

#include <stdio.h>
#include <string.h>

#define LUNG_MAX 50

int modul1(char a[], char b[], int, int);
void modul2(int);
int main()
{
    char cuv_in[LUNG_MAX];
    char cuv[LUNG_MAX];
    
    printf("Programul se opreste la stop \n");
    printf("Introdu primul sir: \n");
    // citire cuvant initial
    scanf("%s", cuv_in);
    int lungime1 = strlen(cuv_in);
    // boolean
    int ok = 0;
    while(1)
    {
        printf("Introdu sir: \n");
        scanf("%s", cuv);
        if (strcmp(cuv, "stop") == 0) break;
        int lungime2 = strlen(cuv);
        ok = modul1(cuv_in, cuv, lungime1, lungime2);
        if (ok == 0) break;
        
    }
    modul2(ok);
    
}