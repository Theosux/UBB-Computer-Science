import socket
import sys

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
c.connect((sys.argv[1], int(sys.argv[2])))		#adresa e un tuplu (ip, port), int pentru a transforma in int, htons si inet_addr le face Py singur

sir1 = input("Introdu primul sir de numere: ")
sir2 = input("Introdu al doilea sir de numere: ")

c.sendall(sir1.encode().ljust(50, b'\0'))		#serverul va face recv(... , 50, MSG_WAITALL) deci vrea 50 de bytes 
c.sendall(sir2.encode().ljust(50, b'\0'))		#encode transforma textul din python in bytes; ljust completeaza la dreapta cu cu 0 pana la 50; sendall e send

sir3 = c.recv(50, socket.MSG_WAITALL)
print("Sir nr comune:", sir3.decode().rstrip('\0'))
c.close()
