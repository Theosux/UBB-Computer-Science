def suma_divizori_proprii(d):
    """
    calculeaza suma numerelor din d
    input: d - o lista de numere intregi (divizori)
    output: suma, rezultat intreg
    """
    s=0
    for el in d:
        s+=el
    return s


def divizori_proprii(n):
    """
    creeaza o lista care contine divizorii proprii ai unui numar
    input: n - numar intreg
    output: divizori - lista divizorilor, numere intregi
    """
    divizori = []
    if n==0 or n==1:
        return []
    i=1
    while i<=n // 2:
        if n%i == 0:
            divizori.append(i)
        i+=1
    return divizori


def citire():
    """
    citeste de la utilizator un numar
    input: -
    output: n, nr intreg
    raises: ValueError, va citi din nou
    """
    while True:
        try:
            n=int(input("Da-mi numarul: "))
            return n
        except ValueError:
            print("Te rog introdu un numar")



def gasire_nr(n):
    """
    afiseaza cel mai mare numar perfect mai mic sau egal ca n
    input: n, nr intreg
    output: -
    raises: , in cazul in care acesta nu exista se afiseaza un mesaj
    """
    while True:
        if n<=2:
            print("Nu exista un numar perfect mai mic decat numarul dat")
            return
        divizori = divizori_proprii(n)
        s=suma_divizori_proprii(divizori)
        if s==n:
            print(f"Cel mai mare numar perfect mai mic decat cel dat este {n}")
            return 0
        n-=1
        
        
        


def main():
    nr=citire()
    nr-=1
    gasire_nr(nr)

main()

    
