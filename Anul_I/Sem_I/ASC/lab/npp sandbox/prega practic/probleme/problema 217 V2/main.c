#include <stdio.h>
#include <string.h>
#define LUNG_MAX 50

int modul1(int v[]);

int main()
{
    int n;
    int m[LUNG_MAX][LUNG_MAX];
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        int y=0;
        while(scanf("%d", &m[i][y]) == 1)
        {
            y++;
            char c = getchar();
            if (c == '\n') break;
        }
        m[i][y] = 0;
    }
    int nr = 0;
    for(int i=0; i<n; i++)
    {
        nr = modul1(m[i]);
        if (nr == 0)
            printf("nu exista");
        else
            printf("%d", nr);
        printf("\n");
    }
}