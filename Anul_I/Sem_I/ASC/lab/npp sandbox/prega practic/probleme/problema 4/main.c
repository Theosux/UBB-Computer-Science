//Se da un sir de numere. Sa se afiseze valorile in baza 16 si in baza 2.

#include <stdio.h>
#include <string.h>

void modul1(int, char s2[]);
void modul2(int, char s2[]);

int main()
{
    int s[50];
    char s2[50];
    char s3[50];
    int n = 0;
    printf("Introduceti sirul de numere: ");
    while(scanf("%d", &s[n]) == 1)
    {
        n++;
        char c = getchar();
        if (c == '\n') break;
    }
    int lungime = n;
    n = 0;
    printf("Sirul baza 16 este: \n");
    while(1)
    {
        int a = s[n];
        modul1(a, s2);
        printf("%s ", s2);
        n++;
        if (n>=lungime) break;
    }
    printf("\n");
    n = 0;
    printf("Sirul baza 2 este: \n");
    while(1)
    {
        int a = s[n];
        modul2(a, s3);
        printf("%s ", s3);
        n++;
        if (n>=lungime) break;
    }
    
    return 0;
}