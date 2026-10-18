#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l;

	s = socket(AF_INET, SOCK_STREAM, 0);
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

	listen(s, 5);

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while (1) {
		uint16_t a = 0;
		char sir[50];
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a connectat un client.\n");

		//aici lucram cu clientul
		recv(c, &sir, sizeof(sir), MSG_WAITALL);

		//lucru cu sirul start
		for (int i = 0; sir[i] != '\0'; i++) {
			if (sir[i] == ' '){
				a++;
			}
		}
		//lucru cu sirul over
		a = htons(a);
		send(c, &a, sizeof(a), 0);
		close(c);
		//sfarsit lucrul cu clientul
	}
}
