#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

void trimite_u16(int c, uint16_t x) { x = htons(x); send(c, &x, 2, 0); }

void citeste(int c, void *buf, int n) {
        int r = recv(c, buf, n, MSG_WAITALL);
        if (r != n) {
                printf("Serverul a inchis conexiunea (am primit %d din %d bytes)\n", r, n);
                exit(1);
        }
}

uint16_t citeste_u16(int c) { uint16_t x; citeste(c, &x, 2); return ntohs(x); }

int citeste_text0(int c, char *buf) { // citim pana la  \0
        int n = 0;
        while (1) {
                citeste(c, &buf[n], 1);
                if (buf[n] == 0) break;
                n++;
        }
        return n;
}

int citeste_bucata(int c, char *buf, int max) {
	int n =0;
	while(n < max - 1) {
		char ch;
		int r = recv(c, &ch, 1, 0);
		if (r <= 0) {
			if (n == 0) return -1;
			break;
		}
		if (ch == 0x0a) break;
		buf[n++] = ch;
	}
	buf[n] = 0;
	return n;
}

int main(int argc, char *argv[]) {
        int c;
        struct sockaddr_in server;

        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0) {
                printf("Eroare la crearea socketului client\n");
                return 1;
        }
        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[2]));      // port dat ca argument
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(argv[1]); // ip dat ca argument

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la conectarea la server\n");
                return 1;
        }

        // aici vorbim cu serverul

	//3908
	uint16_t id = 67;
	trimite_u16(c, id);

	//prima lungime
	uint16_t l = citeste_u16(c);
	uint16_t l1 = l+1;
	//primul mesaj
	char msg1[l1];
	citeste(c, msg1, l);
	msg1[l] = 0;
	printf("%s\n", msg1);

	//trimitere lungime
	trimite_u16(c, l);

	//citirea pe bucati
	static char text[65536];
	uint16_t nr = 0, total = 0, litere = 0;	// nr bucati; total; nr litere; suma
        uint32_t suma = 0;

	while (1) {
                unsigned char lb;
                citeste(c, &lb, 1);
                if (lb == 0) break;
                citeste(c, text + total, lb);
                nr++;
                total += lb;
        }

	for (int i = 0; i < total; i++) {
                unsigned char ch = text[i];
                if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
                        litere++;
                        suma += i;
                }
        }
        printf("bucati=%u total=%u litere=%u suma=%u\n", nr, total, litere, suma);

        trimite_u16(c, nr);
        trimite_u16(c, total);
        trimite_u16(c, litere);

        //pozitia
        uint16_t poz = citeste_u16(c);
        printf("poz=%u\n", poz);
        send(c, text + poz, 8, 0);

        //suma pozitiilor literelor
        uint32_t s = htonl(suma);
        send(c, &s, 4, 0);
	//gata
        close(c);
}
