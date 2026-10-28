#include <stdio.h>

int verifica_numar(int nr, int n);
void afiseaza_total(int sum);

int main()
{
    int n = 0;
    int suma_totala = 0;
    int nr;
    
    printf("N: ");
    scanf("%d", &n);
    getchar();
    printf("\n \n");
    
    while(1)
    {
        printf("Numar: ");
        scanf("%x", &nr);
        getchar();

        
        if(nr == 0) break;
        
        int sum = verifica_numar(nr, n);
        if (sum != 0)
        {
            printf("%x, %d \n", nr, sum);
            suma_totala = suma_totala + sum;
        }
            printf("\n");
    }
    
    if(suma_totala > 0)
    afiseaza_total(suma_totala);

    else
        printf("Nu mi-ai dat niciun numar care sa respecte cerinta si care sa fie nenul");
    
    
    return 0;
}