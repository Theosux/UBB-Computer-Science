#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

void citeste(int c, void *buf, int n) {
        int r = recv(c, buf, n, MSG_WAITALL);
        if (r != n) {
                printf("Serverul a inchis conexiunea (am primit %d din %d bytes)\n", r, n);
                exit(1);
        }
}

void trimite_u16(int c, uint16_t x) {
	x = htons(x);
	send(c, &x, 2, 0);
}

uint32_t citeste_u32(int c) {
	uint32_t x;
	citeste(c, &x, 4);
	return ntohl(x);
}

void trimite_u32(int c, uint32_t x) {
	x = htonl(x);
	send(c, &x, 4, 0);
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
	char msg1[256];
	citeste(c, msg1, 256);
	msg1[256] = 0;
	printf("%s\n", msg1);

	//trimit 2026 ca uint16_t
	uint16_t x;
	x = 2026;
	trimite_u16(c, x);


	char msg2[256];
	citeste(c, msg2, 256);
	msg2[256] = 0;
	printf("%s\n", msg2);


	uint32_t a = citeste_u32(c);
	a = a*2;
	trimite_u32(c, a);

	char msg3[256];
        citeste(c, msg3, 256);
        msg3[256] = 0;
        printf("%s\n", msg3);

	char nume[32];
	memset(nume, 0, sizeof(nume));
	strcpy(nume, "Teo");
	send(c, nume, 32, 0);

        char msg4[256];
        citeste(c, msg4, 256);
        msg4[256] = 0;
        printf("%s\n", msg4);

	// gata vorba cu serveru
	close(c);
}
