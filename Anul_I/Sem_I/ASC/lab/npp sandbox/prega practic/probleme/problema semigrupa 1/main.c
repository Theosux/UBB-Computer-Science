
#include <stdio.h>
#include <string.h>
#define LUNG_MAX 50

void modul1(char s[], char s2[]);

int main()
{
    char s[LUNG_MAX];
    char s2[LUNG_MAX];
    char m[LUNG_MAX][LUNG_MAX];
    int n;
    printf("Introdu nr de cuvinte: \n");
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        printf("Introdu n cuvinte: ");
        scanf("%s", s);
        modul1(s, s2);
        strcpy(m[i], s2);
        // m[i] = s2;
        printf("\n");
    }
    printf("cuvintele sunt: ");
    for(int i = 0; i < n; i++)
    {
        printf("%s", m[i]);
        printf("\n");
    }
    return 0;
}