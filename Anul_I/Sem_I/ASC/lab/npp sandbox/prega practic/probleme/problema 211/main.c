/*
Fie programul main.c in care se citeste de la tastatura un numar natural N,
N secvente de caractere care respecta formatul
(litere mici, litere mari si cifre care formeaza diferite cuvinte separate prin caracterul /) 
si un numar natural M.
Programul principal va apela pentru fiecare secventa | (1<=|<=N) de caractere citita procedura
VERIFICARE definita in modul1 asm care va afisa al I-lea cuvant (considerand separarea dupa caracterul /),
daca acesta exista si daca numarul de vocale este egal cu numarul M citit de la tastatura.
Tot in cadrul programului principal se va afisa prin utilizarea procedurii
CONTOR definita in modul2.asm cate vocale litere mari sunt in total in secventele citite.
Ex:
Puncte
Fără notă
Daca se citeste:
N=4 secvente:
- Avea/ana/3/mERe/dar/nu/avea/Pere
- azi/ninge/afAra
- nu/iMi/place/frigul
- Vreau/sA/imi/cumperi/inghetatA
M=3
Se va afisa:
Avea cumperi
7
*/

#include <stdio.h>


int main()
{
    int n = 0;
    printf("N: ");
    scanf("%d", &n);
    
    return 0;
}