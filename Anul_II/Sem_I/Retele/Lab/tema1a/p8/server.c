#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

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
                char sir1[50], sir2[50], sir3[50];
                memset(sir3, 0, sizeof(sir3));
                c = accept(s, (struct sockaddr *) &client, &l);
                printf("S-a conectat un client.\n");
                // aici lucram cu clientul
                recv(c, &sir1, sizeof(sir1), MSG_WAITALL);
                recv(c, &sir2, sizeof(sir2), MSG_WAITALL);
                //lucru cu siruri start
                int arr1[50]; // facem un prim array de numere
		int cnt1 = 0;

		char *t = strtok(sir1, " ");

		while(t != NULL) {
			arr1[cnt1] = atoi(t);
			cnt1++;

			t = strtok(NULL, " ");
		}

		int arr2[50]; // la fel si al doilea array
		int cnt2 = 0;

		char *tt = strtok(sir2, " ");

		while(tt != NULL) {
			arr2[cnt2] = atoi(tt);
			cnt2++;

			tt = strtok(NULL, " ");
		}

		//acum gasim termeni comuni in array
		int arr3[50];
		int cnt3 = 0;
		for(int i = 0; i < cnt1; i++) {
			for(int j = 0; j < cnt2; j++) {
				if (arr1[i] == arr2[j]) {
					arr3[cnt3] = arr1[i];
					cnt3++;
					break;
				}
			}
		}
		//transormam arr3 in sir3
		int offset = 0;
		for(int i = 0; i < cnt3; i++) {
			offset += sprintf(sir3 + offset, "%d ", arr3[i]);
		}
                //lucru cu siruri over
                send(c, &sir3, sizeof(sir3), 0);
                close(c);
                // sfarsitul lucrului pt client
        }
}
