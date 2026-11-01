#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>

uint16_t cmmdc(uint16_t a, uint16_t b) {
	//Euclid
	while (b != 0) {
		uint16_t r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main() {
	int s;
	struct sockaddr_in server, client;
	int l;
	uint16_t nr[2];		//cele doua nr primite
	uint32_t rez[2];	//rez[0] = cmmd, rez[1] = cmmc
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socketului server\n");
		return 1;
	}
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}
	//dispare listen

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1) {
		//asteptam datagrama
		recvfrom(s, nr, sizeof(nr), 0, (struct sockaddr *) &client, &l);
		uint16_t a = ntohs(nr[0]);
		uint16_t b = ntohs(nr[1]);
		printf("Am primit %hu si %hu de la %s:%hu\n", a, b, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		uint16_t d = cmmdc(a, b);
		uint32_t m = 0;
		if (d != 0)
			m = (uint32_t) a / d * b;

		rez[0] = htonl(d);
		rez[1] = htonl(m);
		//raspundem la adresa din client
		sendto(s, rez, sizeof(rez), 0, (struct sockaddr *) &client, sizeof(client));
	}
}
