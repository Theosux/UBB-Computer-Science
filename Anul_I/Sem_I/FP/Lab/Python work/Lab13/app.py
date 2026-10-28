import sys

def citire_date():
    """
    Citeste valorile monedelor si suma S.
    """
    monede = []
    print("Introduceti valoarea unei monede, sau '0' pt a termina:")

    while True:
        try:
            val = int(input())
            if val == 0:
                break
            if val < 0:
                print("Valoarea trb sa fie pozitiva.")
                continue
            monede.append(val)
        except ValueError:
            print("Introduceti un numar intreg.")
    
    if not monede:
        print("Nu au fost introduse monede.")
        sys.exit()

    while True:
        try:
            S = int(input("Introduceti suma S: "))
            if S < 0:
                print("Suma trb sa fie pozitiva.")
                continue
            break
        except ValueError:
            print("Introduceti un numar intreg.")
            
    #returnam lista sortata
    return sorted(monede), S




# Varianta 1: Backtracking recursiv

def backtracking_r(monede, S, solutie_curenta, index):
    """
    monede = vector ce contine valorile
    S = suma la care trb sa ajungem
    solutie_curenta = permutare corecta la care ne aflam
    index = indexul permutarii
    """
    
    suma_curenta = sum(solutie_curenta)

    if suma_curenta == S:
        print("Solutie gasita:", solutie_curenta)
        return True 

    if suma_curenta > S:
        return False

    gasit_ceva = False 
    for i in range(index, len(monede)):
        solutie_curenta.append(monede[i])
        if backtracking_r(monede, S, solutie_curenta, i):
            gasit_ceva = True 
        solutie_curenta.pop()
    
    return gasit_ceva




# Varianta 2: Backtracking iterativ
def backtracking_i(monede, S):
    """
    Docstring for backtracking_i
    """
    found = False
    n = len(monede)
    x = [-1]        # stocam indicii

    while len(x) > 0:
        choosed = False
        suma_fixata = sum([monede[i] for i in x[:-1]])

        while not choosed and x[-1] < n-1:
            x[-1] = x[-1] + 1
            if len(x) > 1 and x[-1] < x[-2]:
                continue
            
            if suma_fixata + monede[x[-1]] <= S:
                choosed = True
        
        if choosed:
            solutie_temp = [monede[i] for i in x]
            suma_temp = suma_fixata + monede[x[-1]]
            
            solutie_valori = solutie_temp
            suma_finala = suma_temp

            if suma_finala == S:
                found = True
                print("Solutie gasita:", solutie_valori)

            else:
                x.append(-1)
        else:
            x.pop()
    return found




def main():
    monede, S = citire_date()

    print("\n Backtracking recursiv ")
    if not backtracking_r(monede, S, [], 0):
        print("Nu exista solutie.")
    
    print("\n Backtracking iterativ ")
    if not backtracking_i(monede, S):
        print("Nu exista solutie.")

main()