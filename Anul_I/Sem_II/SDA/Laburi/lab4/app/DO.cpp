#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

int DO::aloca() {
	//	theta(1)
	int i = primLiber;
	if (i != -1) {
		primLiber = urm[primLiber];
	}
	return i;
}

void DO::dealoca(int i) {
	// theta(1)
	urm[i] = primLiber;
	primLiber = i;
}

void DO::resize() {
	// theta(n)		n - capacitatea curenta
	TElem* eNou = new TElem[capacitate * 2];
	int* urmNou = new int[capacitate * 2];
	for (int i = 0; i < capacitate; i++) {
		eNou[i] = e[i];
		urmNou[i] = urm[i];
	}
	for (int i = capacitate; i < capacitate * 2 - 1; i++) {
		urmNou[i] = i + 1;
	}
	urmNou[capacitate * 2 - 1] = -1;
	primLiber = capacitate;
	capacitate = capacitate * 2;
	delete[] e;
	delete[] urm;
	e = eNou;
	urm = urmNou;
}

DO::DO(Relatie r) {
	// theta(capacitate)
	this->r = r;
	this->capacitate = 10; // capacitate initiala
	this->e = new TElem[capacitate];
	this->urm = new int[capacitate];
	this->prim = -1;
	this->dimensiune = 0;

	for (int i = 0; i < capacitate - 1; i++) {
		urm[i] = i + 1;
	}
	urm[capacitate - 1] = -1;
	this->primLiber = 0;
}

TValoare DO::adauga(TCheie c, TValoare v) {
	// O(n)			n - nr de elem, caz favorabil theta(1) pt element inserat la inceput, defav theta(n) pt elemnt inserat la final
	int curent = prim;
	int prec = -1;

	// parcurgem lista pt a patra ordinea si verifica daca exista cheia
	while (curent != -1 && r(e[curent].first, c)) {
		if (e[curent].first == c) {
			TValoare veche = e[curent].second;
			e[curent].second = v;
			return veche;
		}
		prec = curent;
		curent = urm[curent];
	}
	// daca relatia e stricata ne asiguram ca ne oprim
	if (curent != -1 && e[curent].first == c) {
		TValoare veche = e[curent].second;
		e[curent].second = v;
		return veche;
	}

	// alocam spatiu
	if (primLiber == -1) {
		resize();
	}

	int nou = aloca();
	e[nou].first = c;
	e[nou].second = v;

	// inseram nodul
	if (prec == -1) {
		urm[nou] = prim;
		prim = nou;
	}
	else {
		urm[nou] = curent;
		urm[prec] = nou;
	}

	dimensiune++;
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	// O(n)				n - nr de elem, caz favorabil theta(1) pt elementul cautat este primul din dict, defavorabil theta(n), elementul se afla la final sau nu se gaseste
	int curent = prim;
	while (curent != -1) {
		if (e[curent].first == c) {
			return e[curent].second;
		}
		curent = urm[curent];
	}
	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	// O(n)			n - nr de elem, caz favorabil theta(1) pt elementul cautat este primul din dict, defavorabil theta(n), elementul se afla la final sau nu se gaseste
	int curent = prim;
	int prec = -1;

	// Cautam cheia de sters
	while (curent != -1 && e[curent].first != c) {
		prec = curent;
		curent = urm[curent];
	}

	// Daca o gasim
	if (curent != -1) {
		if (prec == -1) {
			prim = urm[prim];
		}
		else {
			urm[prec] = urm[curent];
		}
		TValoare val = e[curent].second;
		dealoca(curent);
		dimensiune--;
		return val;
	}

	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	// theta(1)
	return dimensiune;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	// theta(1)
	return dimensiune == 0;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	delete[] e;
	delete[] urm;
}
