char linie[1024], raspuns[1024];

// scot numere dintr-un text cu format cunoscut
int a, b;
char op;
sscanf(linie, "CALCUL %d %c %d", &a, &op, &b);

// construiesc un text din numere
sprintf(raspuns, "%d", a + b);

// lipesc mai multe numere intr-un singur text, separate prin spatiu
int offset = 0;
for (int i = 0; i < n; i++)
    	offset += sprintf(raspuns + offset, i == 0 ? "%d" : " %d", v[i]);

// sparg un text in cuvinte / numere
char *t = strtok(linie, " ");
while (t != NULL) {
    	int x = atoi(t);
    	t = strtok(NULL, " ");
}
