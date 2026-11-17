#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int conecteaza(char *ip, int port) {
        int c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0) { printf("Eroare la crearea socketului client\n"); exit(1); }
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_port = htons(port);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ip);
        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la conectarea la server\n");
                exit(1);
        }
        return c;
}

void dump(unsigned char *buf, int n) {
        for (int i = 0; i < n; i += 16) {
                printf("%04x  ", i);
                for (int j = i; j < i + 16; j++) {
                        if (j < n) printf("%02x ", buf[j]);
                        else printf("   ");
                }
                printf(" |");
                for (int j = i; j < i + 16 && j < n; j++)
                        printf("%c", (buf[j] >= 32 && buf[j] < 127) ? buf[j] : '.');
                printf("|\n");
        }
}

int main(int argc, char *argv[]) {
        int c = conecteaza(argv[1], atoi(argv[2]));
        unsigned char buf[4096];
        sleep(1);
        int n = recv(c, buf, sizeof(buf), 0);
        printf("recv a intors %d bytes\n", n);
        if (n > 0) dump(buf, n);
        if (n >= 4) {
                uint16_t a; uint32_t b;
                memcpy(&a, buf, 2);
                memcpy(&b, buf, 4);
                printf("primii 2 bytes ca uint16: ntohs = %u\n", ntohs(a));
                printf("primii 4 bytes ca uint32: ntohl = %u\n", ntohl(b));
        }
        close(c);
}
