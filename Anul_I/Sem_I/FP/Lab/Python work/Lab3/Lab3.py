def citire_numere():
    
    """
    citeste o lista de la utilizator pana cand primeste 'STOP'
    input: -
    output: numere - lista de numere intregi citita de la tastatura
    raises: ValueError - continua citirea
    """
    
    i = 0
    numere=[]
    while True:
        numar=input(f"Da numarul {i}: ")
        if numar == "STOP":
            break
        try:
            numar = int(numar)
        except ValueError:
            continue
        numere.append(numar)
        i += 1
    return numere



def cmmdc(a,b):
    
    """
    calculeaza cmmdc prin algoritmul lui Euclid si il transforma pe primul nr in acesta
    input: a,b - numere intregi
    output: a - numar intreg
    """
    
    while b != 0:
        a,b = b,a % b
    return a

def prim(a):
    
    """
    returneaza True pentru a - nr prim, altfel returneaza False
    input: a - numar intreg
    output: True/False
    """
    a = abs(a)
    if a < 2:
        return False
    i = 2
    while i*i <= a:
        if a % i == 0:
            return False
        i += 1
    return True

def unu(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga de numere crescatoare
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """
    
    start = 0
    best_start = 0
    maxlength = 1
    for i in range(1, len(l)):
        if l[i] <= l[i-1]:
            start = i
        else:
            length = i-start+1
            if length > maxlength:
                maxlength = length
                best_start = start
    return l[best_start:best_start + maxlength]

def doi(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga in care exista maxim 3 numere distincte
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """
    
    if len(set(l)) <= 3:
        return l
    temp = []
    secventa = []
    for x in l:
        if len(set(temp)) <= 2 or x in temp:
            temp.append(x)
            if len(temp)>len(secventa):
                secventa = temp.copy()
        if len(set(temp)) == 3 and x not in temp:
            a = temp[0]
            last_index_a = len(temp) -1 - temp[::-1].index(a)
            temp = temp[last_index_a +1:]
            temp.append(x)
            if len(temp)>len(secventa):
                secventa = temp.copy()
    return secventa      

def trei(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga in care termeni consecutivi sunt primi intre ei
    functia se foloseste si de functia cmmdc
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """

    temp = []
    secventa = []
    temp.append(l[0])
    p = l[0]
    for x in l[1:]:
        if cmmdc(p,x) == 1:
            temp.append(x)
        else:
            temp = []
            temp.append(x)
        if len(temp) > len(secventa):
            secventa = temp.copy()
        p = x
    return secventa

def patru(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga de numere prime
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """

    temp = []
    secventa = []
    for x in l:
        if prim(x):
            temp.append(x)
        else:
            temp = []
        if len(temp) > len(secventa):
            secventa = temp.copy()
    return secventa

def cinci(l):
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga ce contine acelasi element
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """

    if len(set(l)) == 1:
        return l
    temp = []
    secventa = []
    for x in l:
        if x in temp:
            temp.append(x)
        else:
            temp = [x]
        if len(temp) > len(secventa):
            secventa = temp.copy()
    return secventa

    
def sase(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga de numere distincte
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """
    
    if len(l) == len(set(l)):
        return l
    temp = []
    secventa = []
    for x in l:
        if x in temp:
            i = temp.index(x)
            temp = temp[i+1:]
        temp.append(x)
        if len(temp)>len(secventa):
            secventa = temp.copy()
    return secventa

def sapte(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga de numere, unde cele consecutive difera printr-un numar prim
    functia se foloseste si de functia prim
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """

    temp = []
    secventa = []
    temp.append(l[0])
    p = l[0]
    for x in l[1:]:
        if prim(x-p):
            temp.append(x)
        else:
            temp = []
            temp.append(x)
        p = x
        if len(temp)>len(secventa):
            secventa = temp.copy()
    return secventa

def opt(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga de numere de la 0 la 10
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """

    temp = []
    secventa = []
    for x in l:
        if x >= 0 and x <= 10:
            temp.append(x)
        else:
            temp = []
        if len(temp)>len(secventa):
            secventa = temp.copy()
    return secventa

def noua(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga de numere care are o valoare care se repeta in oricare trei elemente consecutive
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """

    if 0 < len(l) < 3:
        return l
    temp = [l[0],l[1]]
    secventa = []
    for i in range(2, len(l)):
        if len(set([temp[-1], temp[-2], l[i]])) <= 2:
            temp.append(l[i])
        else:
            temp = [temp[-1], l[i]]
        if len(temp)>len(secventa):
            secventa = temp.copy()
    return secventa


def zece(l):
    
    """
    se foloseste de metoda sliding window pentru a gasi secventa cea mai lunga de numere oscilante
    input: l - lista de numere intregi
    output: secventa - lista corespunzatoare secventei
    """
    
    if len(l) == 1:
        return l
    temp = []
    secventa = []
    temp.append(l[0])
    p = l[0]
    d1 = 0
    d2 = 0
    for x in l[1:]:
        if x>p:
            d2 = 1
        elif x<p:
            d2 = -1
        if x == p:
            d1 = d2
        if d2 != d1:
            temp.append(x)
            d1 = d2
        else:
            temp = []
            temp.append(x)
            d1 = 0
        p = x
        if len(temp)>len(secventa):
            secventa = temp.copy()
    return secventa

def testari():
    
    """
    testeaza corectitudinea functiilor pentru anumite proprietati folosind cazuri date si raspunsul lor corect
    input: -
    output: -
    raises: AssertionError - in cazul in care functia este gresita
    """
    
    assert noua([1, 2]) == [1, 2]
    assert noua([1, 5, 2, 3, 6, 2, 6, 7, 2]) == [6, 2, 6]
    assert zece([1, 2, 1, 3, 2, 7, 8, 9, 10]) == [1, 2, 1, 3, 2, 7]
    assert zece([3, 4, 5, 2, 3, 7, 8, 1, 9, 10, 1]) == [7, 8, 1, 9]
    
               
        
    

def main ():
    print("Lista comenzi: \n CITIRE = Citirea unei liste de numere intregi \n 1->16 = Alegerea uneia dinre proprietati \n STOP = Iesire din aplicatie/Oprit citire numere")
    numere = []
    while True:
        comanda = input("Introduce comanda: ")
        if comanda == "CITIRE":
            numere = citire_numere()
            print("Se cauta secventa de lungime maxima care satisface proprietatea aleasa")
            
        elif comanda == "1":
            print("Ai ales proprietatea 1")
            print("Sirul este strict crescator")
            print(unu(numere))
            
        elif comanda == "2":
            print("Ai ales proprietatea 2")
            print("Sirul contine maxim 3 elemente distincte")
            print(doi(numere))
            
        elif comanda == "3":
            print("Ai ales proprietatea 3")
            print("Sirul contine termeni consecutiv primi intre ei")
            print(trei(numere))

        elif comanda == "4":
            print("Ai ales proprietatea 4")
            print("Sirul contine termeni primi")
            print(patru(numere))

        elif comanda == "5":
            print("Ai ales proprietatea 5")
            print("Sirul are doar termeni egali")
            print(cinci(numere))

        elif comanda == "6":
            print("Ai ales proprietatea 6")
            print("Sirul contine doar elemente distincte intre ele")
            print(sase(numere))
            
        elif comanda == "7":
            print("Ai ales proprietatea 7")
            print("Sirul are proprietatea ca doua elemente consecutive difera printr-un nr prim")
            print(sapte(numere))

        elif comanda == "8":
            print("Ai ales proprietatea 8")
            print("Sirul contine elemente de la 0 la 10")
            print(opt(numere))

        elif comanda == "9":
            print("Ai ales proprietatea 9")
            print("Sirul contine un element care se repeta in grupe de cate 3 elemente consecutive")
            print(noua(numere))

        elif comanda == "10":
            print("Ai ales proprietatea 10")
            print("Sirul oscileaza la fiecare valoare (x[i+1]-x[i] are semn diferit fata de x[i+2]-x[i+1])")
            print(zece(numere))
            
        elif comanda == "11":
            print("Ai ales proprietatea 11")

        elif comanda == "12":
            print("Ai ales proprietatea 12")

        elif comanda == "13":
            print("Ai ales proprietatea 13")

        elif comanda == "14":
            print("Ai ales proprietatea 14")

        elif comanda == "15":
            print("Ai ales proprietatea 15")

        elif comanda == "16":
            print("Ai ales proprietatea 16")
        elif comanda == "STOP":
            print("Programul s-a incheiat")
            break #exit
        else:
            print(f"Nu stiu comanda {comanda}")


testari()
main()
