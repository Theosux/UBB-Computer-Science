#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	int c;
	struct sockaddr_in server;
	uint16_t a, b;
	uint16_t nr[2];
	uint32_t rez[2];

	c = socket(AF_INET, SOCK_DGRAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(atoi(argv[2]));		// port dat ca argument
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);	// ip dat ca argument

	printf("a = ");
	scanf("%hu", &a);
	printf("b = ");
	scanf("%hu", &b);

	nr[0] = htons(a);
	nr[1] = htons(b);

	sendto(c, nr, sizeof(nr), 0, (struct sockaddr *) &server, sizeof(server));

	recvfrom(c, rez, sizeof(rez), 0, NULL, NULL);
	printf("cmmdc = %u\n", ntohl(rez[0]));
	printf("cmmmc = %u\n", ntohl(rez[1]));
	close(c);
}
