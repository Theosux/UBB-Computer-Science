// Se citeste de la tastatura un sir de caractere
//(litere mici si litere mari, cifre, caractere speciale, etc).
//Sa se formeze un sir nou doar cu literele mici si un sir nou doar cu literele mari.
//Sa se afiseze cele 2 siruri rezultate pe ecran.

#include <stdio.h>

void modul1(char s[], char s1[]);
void modul2(char s[], char s2[]);

int main()
{
    char s[100], s1[100], s2[100];
    
    printf("Introdu propozitia: ");
    fgets(s, 101, stdin);
    
    modul1(s, s1);
    modul2(s, s2);
    
    printf("Prima propozitie este %s \n", s1);
    printf("A doua propozitie este %s \n", s2);
    
    return 0;
}