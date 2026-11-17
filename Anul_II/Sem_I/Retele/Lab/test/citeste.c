// * Functia citeste
void citeste(int c, void *buf, int n) {
    	int r = recv(c, buf, n, MSG_WAITALL);
    	if (r != n) {
        	printf("Serverul a inchis conexiunea (am primit %d din %d bytes)\n", r, n);
        	exit(1);
    	}
}


// * Pt numere de diferite bytes

uint8_t  citeste_u8(int c)  { uint8_t x;  citeste(c, &x, 1); return x; }
uint16_t citeste_u16(int c) { uint16_t x; citeste(c, &x, 2); return ntohs(x); }
uint32_t citeste_u32(int c) { uint32_t x; citeste(c, &x, 4); return ntohl(x); }
int32_t  citeste_i32(int c) { int32_t x;  citeste(c, &x, 4); return ntohl(x); }

void trimite_u8(int c, uint8_t x)   { send(c, &x, 1, 0); }
void trimite_u16(int c, uint16_t x) { x = htons(x); send(c, &x, 2, 0); }
void trimite_u32(int c, uint32_t x) { x = htonl(x); send(c, &x, 4, 0); }

// * Text de lungime fixa

// PRIMESC un mesaj de exact 256 de bytes (textul + \0-uri pana la 256)
char msg[257];
citeste(c, msg, 256);
msg[256] = 0;              // siguranta: daca textul umple tot, tot am un \0 la final
printf("%s\n", msg);

// TRIMIT un nume ca sir de exact 32 de bytes
char nume[32];
memset(nume, 0, sizeof(nume)); // toti cei 32 de bytes devin \0
strcpy(nume, "Teo");
send(c, nume, 32, 0);          // 32, nu strlen(nume)!


// * Text cu lungimea in fata
int citeste_text_len(int c, char *buf) {
    	uint16_t n = citeste_u16(c);
    	citeste(c, buf, n);
    	buf[n] = 0;
    	return n;
}void trimite_text_len(int c, char *s) {
    	uint16_t n = strlen(s);
    	trimite_u16(c, n);
    	send(c, s, n, 0);
}


// * Text care se termina cu \0
int citeste_text0(int c, char *buf) {
    	int n = 0;
    	while (1) {
        	citeste(c, &buf[n], 1);
        	if (buf[n] == 0) break;
        	n++;
    	}
    	return n;
}void trimite_text0(int c, char *s) {
    	send(c, s, strlen(s) + 1, 0);
}


// * Linie terminata cu \n
int citeste_linie(int c, char *buf) {
    	int n = 0;
    	char ch;
    	while (1) {
        	citeste(c, &ch, 1);
        	if (ch == '\n') break;
        	buf[n++] = ch;
    	}
    	buf[n] = 0;
    	return n;
}void trimite_linie(int c, char *s) {
    	send(c, s, strlen(s), 0);
    	send(c, "\n", 1, 0);
}

// * Sir de numere, intai cate sunt apoi numerele
// PRIMESC: uint16_t n, apoi n numere uint32_t
uint16_t n = citeste_u16(c);
uint32_t v[1000];
for (int i = 0; i < n; i++)
    	v[i] = citeste_u32(c);

// TRIMIT: acelasi format inapoi
trimite_u16(c, n);
for (int i = 0; i < n; i++)
    	trimite_u32(c, v[i]);



// * Numere din buffer
// am un buffer buf (deja citit) si stiu ca la pozitia 3 incepe un uint16_t
// si la pozitia 5 un uint32_t
uint16_t a;
uint32_t b;
memcpy(&a, buf + 3, 2);
memcpy(&b, buf + 5, 4);
a = ntohs(a);
b = ntohl(b);
printf("a = %u, b = %u\n", a, b);

// * Multe date
// ** n bytes, suma lor
// cand n poate fi mare (sute de mii), nu pune buffer-ul pe stiva
unsigned char *d = malloc(n);
citeste(c, d, n);            // MSG_WAITALL: asteapta pana vin toti n bytes
uint32_t suma = 0;
for (int i = 0; i < n; i++)
    	suma += d[i];            // unsigned char: 0..255, nu negativ
free(d);

// ** bucla echivalenta
// ce face MSG_WAITALL "pe dinauntru": aduna bucati pana are toti cei n bytes
int total = 0;
while (total < n) {
    	int r = recv(c, buf + total, n - total, 0);
    	if (r <= 0) {
        	printf("Serverul a inchis conexiunea\n");
        	exit(1);
    	}
    	total += r;
}


// * Doua conexiuni
int c  = conecteaza(argv[1], atoi(argv[2]));  // prima conexiune
// ... aflu de la server un port nou ...
int c2 = conecteaza(argv[1], port_nou);        // a doua, la acelasi IP
trimite_u32(c2, ceva);                         // vorbesc pe c2
close(c2);
// c e inca deschisa, continui pe ea
