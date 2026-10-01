#ifndef DOMAIN_H
#define DOMAIN_H

typedef struct {
	int id;
	char tip[100];
	char producator[100];
	char model[100];
	int pret;
	int cantitate;
} Produs;
Produs create(int id, const char* tip, const char* producator, const char* model, int pret, int cantitate);
#endif