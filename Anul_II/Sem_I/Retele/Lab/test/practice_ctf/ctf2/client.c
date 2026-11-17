#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void citeste(int c, void *buf, int n) {
        int r = recv(c, buf, n, MSG_WAITALL);
        if (r != n) {
                printf("Serverul a inchis conexiunea (am primit %d din %d bytes)\n", r, n);
                exit(1);
        }
}

int citeste_text0(int c, char *buf) {
	int n = 0;
       	while (1) {
                citeste(c, &buf[n], 1);
                if (buf[n] == 0) break;
                n++;
        }
        return n;
}

int32_t  citeste_i32(int c) { int32_t x;  citeste(c, &x, 4); return ntohl(x); }
void trimite_i32(int c, int32_t x) { x = htonl(x); send(c, &x, 4, 0); }


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

	char msg1[1024];
	int n = citeste_text0(c, msg1);
	printf("%s\n", msg1);

	int nr = citeste_i32(c);

	nr = 0-nr;

	trimite_i32(c, nr);

	char msg2[1024];
	n = citeste_text0(c, msg2);
	printf("%s\n", msg2);

	// gata
	close(c);
}
