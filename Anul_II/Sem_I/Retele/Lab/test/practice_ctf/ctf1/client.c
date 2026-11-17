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

uint16_t citeste_u16(int c) { uint16_t x; citeste(c, &x, 2); return ntohs(x); }
uint32_t citeste_u32(int c) { uint32_t x; citeste(c, &x, 4); return ntohl(x); }

void trimite_u16(int c, uint16_t x) { x = htons(x); send(c, &x, 2, 0); }
void trimite_u32(int c, uint32_t x) { x = htonl(x); send(c, &x, 4, 0); }

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
	uint16_t l = citeste_u16(c);
	int l1;
	l1 = l+1;
	char msg[l1];
	citeste(c, msg, l);
	msg[l] = 0;
	printf("%s\n", msg);

	uint16_t l2 = 4;
	trimite_u16(c, l2);
	uint16_t l3;
	l3 = l2+1;
	char msgs[l3];
	//memset(msgs, 0, sizeof(msgs));
	strcpy(msgs, "gata");
	send(c, msgs, l2, 0);

	l = citeste_u16(c);
	l1 = l+1;
	char msg1[l1];
	citeste(c, msg1, l);
	msg1[l] = 0;
	printf("%s\n", msg1);


	uint16_t n = citeste_u16(c);
	uint32_t nr;
	uint32_t sum = 0;
	for(int i = 0; i < n; i++) {
		nr = citeste_u32(c);
		sum += nr;
	}
	trimite_u32(c, sum);

	l = citeste_u16(c);
	l1 = l+1;
	char msg2[l1];
	citeste(c, msg2, l);
	msg2[l] = 0;
	printf("%s\n", msg2);

	l = citeste_u16(c);
	l1 = l+1;
	char msg3[l1];
	citeste(c, msg3, l);
	msg3[l] = 0;
	printf("Textul pentru oglindire:\n");
	printf("%s\n", msg3);

	char oglindit[l1];

	for (int i = 0; i < l; i++) {
		oglindit[i] = msg3[l-1-i];
	}

	oglindit[l] = 0;

	trimite_u16(c, l);
	send(c, oglindit, l, 0);

	l = citeste_u16(c);
	l1 = l+1;
	char msg4[l1];
	citeste(c, msg4, l);
	msg4[l] = 0;
	printf("%s\n", msg4);
	//gata
        close(c);
}
