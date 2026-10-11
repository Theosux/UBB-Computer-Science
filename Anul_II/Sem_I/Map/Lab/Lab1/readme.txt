Clase:
NumarComplex                 - numarul complex si operatiile pe el (adunare, scadere, inmultire, impartire)
Operation                    - enum cu cele 4 operatii
ComplexExpression            - clasa abstracta, calculeaza expresia (execute)
Addition/Subtraction/Multiplication/DivisionExpression - cate o subclasa pentru fiecare operatie
ExpressionFactory            - creeaza expresia potrivita pentru operatie
ExpressionParser             - interfata pentru parsare
CommandLineExpressionParser  - verifica si parseaza argumentele din linia de comanda
Main                         - porneste programul si afiseaza rezultatul

Principii SOLID:
SRP - fiecare clasa are o singura treaba: parserul citeste si verifica, factory-ul creeaza
      expresia, expresia calculeaza, NumarComplex face calculele intre doua numere.
OCP - pentru o operatie noua adaug o subclasa noua a lui ComplexExpression si un case in
      factory, fara sa modific execute().
      UML: o noua clasa cu generalizare spre ComplexExpression.
LSP - orice subclasa (AdditionExpression, DivisionExpression...) poate fi folosita in locul
      lui ComplexExpression, execute() merge la fel.
      UML: cele 4 generalizari spre ComplexExpression.
ISP - interfata ExpressionParser are o singura metoda, parse().
DIP - Main lucreaza cu interfata ExpressionParser si cu clasa abstracta ComplexExpression,
      nu cu clasele concrete.
      UML: dependentele din Main merg spre ExpressionParser si ComplexExpression.

Sabloane de proiectare:
Template Method - ComplexExpression.execute() are pasii comuni (parcurge numerele), iar pasul
                  care difera, executeOneOperation(), e abstract si scris in fiecare subclasa.
                  UML: ComplexExpression abstracta (italic), metoda abstracta, 4 generalizari.
Factory         - ExpressionFactory.createExpression() creeaza subclasa potrivita dupa operatie.
                  UML: dependenta <<create>> spre ComplexExpression.
Singleton       - ExpressionFactory are constructor privat si getInstance(), deci exista o
                  singura instanta.
                  UML: constructorul cu "-", instance si getInstance() subliniate (static).


Exemple rulare:

2+3*i + 5-6*i + -2+i ---> 5-2*i
1+i * 1-i ---> 2
1+i / 2 ---> 0.5+0.5*i
1 / 3 ---> 0.33
i * i ---> -1
2.5+1.5*i + 1 ---> 3.5+1.5*i
0 - i ---> 0-1*i
1+i / 0 ---> Eroare: Impartire la zero
2+i + 3 - 4 ---> Expresie invalida: Operatorii trebuie sa fie la fel
2+i + ---> Expresie invalida: Numar gresit de argumente
2+i % 3 ---> Expresie invalida: Operator necunoscut: %
abc + 1 ---> Expresie invalida: For input string: "abc"