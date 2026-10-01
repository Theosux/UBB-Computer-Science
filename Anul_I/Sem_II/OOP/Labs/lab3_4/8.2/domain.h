#ifndef DOMAIN_H
#define DOMAIN_H

typedef struct {
	int id;
	char* tip;
	char* producator;
	char* model;
	int pret;
	int cantitate;
} Produs;
Produs create(int id, const char* tip, const char* producator, const char* model, int pret, int cantitate);

void destroy_produs(Produs* p);
Produs copy_produs(Produs* p);
#endif