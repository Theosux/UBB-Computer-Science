#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int c;
        struct sockaddr_in server;
        char sir1[50], sir2[50], sir3[50];

        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0) {
                printf("Eroare la crearea socketului client\n");
                return 1;
        }
        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[2]));		//port dat ca argument
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(argv[1]);	//ip dat ca argument

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la conectarea la server\n");
                return 1;
        }

        printf("Introdu primul sir de numere: ");
        fgets(sir1, sizeof(sir1), stdin);
        printf("Introdu al doilea sir de numere: ");
        fgets(sir2, sizeof(sir2), stdin);
        send(c, &sir1, sizeof(sir1), 0);
        send(c, &sir2, sizeof(sir2), 0);
        recv(c, &sir3, sizeof(sir3), MSG_WAITALL);
        printf("Sir nr comune: %s\n", sir3);
        close(c);
}
