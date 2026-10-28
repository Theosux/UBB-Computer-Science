
def citire():
    n = int(input("Da-mi numarul: "))
    return n


def prim(n):
    if n==0 or n==1:
        return 1
    i=2
    while i <= n // 2:
        if n%i == 0:
            return 1
        i+=1
    return 0


def gasire(n):
    if n==0 or n==1 or n==2:
        print("Nu exista un astfel de numar")
        return 0
    while prim(n):
        n-=1
    print(n)
    return 0


nr=citire()
gasire(nr-1)

