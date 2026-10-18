#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
	int c;
	struct sockaddr_in server;
	char sir[50];

	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server\n");
		return 1;
	}

	printf("Introdu sirul de numere: ");
	fgets(sir, sizeof(sir), stdin);
	send(c, &sir, sizeof(sir), 0);
	uint16_t a;
	recv(c, &a, sizeof(a), 0);
	a = ntohs(a);
	printf("Nr de spatii este %hu\n", a);
	close(c);
}
