#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

// o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

// complexitate: theta(1)
Multime::Multime() {
	this->radacina = nullptr;
	this->dimensiune = 0;
}

// complexitate: caz fav: theta(1) cazul in care ..., caz med: theta(log n), caz defav: theta(n) (arbore degenerat)
// cauta pozitia si adauga elementul doar daca nu exista deja
bool Multime::adauga(TElem elem) {
	Nod* curent = radacina;
	Nod* parinte = nullptr;

	while (curent != nullptr) {
		if (curent->e == elem) {
			return false; // elementul exista deja, deci nu il adaugam
		}
		parinte = curent;
		if (rel(elem, curent->e)) {
			curent = curent->st;
		}
		else {
			curent = curent->dr;
		}
	}

	Nod* nou = new Nod(elem);
	if (parinte == nullptr) {
		radacina = nou; // arborele era vid
	}
	else if (rel(elem, parinte->e)) {
		parinte->st = nou;
	}
	else {
		parinte->dr = nou;
	}

	dimensiune++;
	return true;
}

// complexitate: caz fav: theta(1), caz mediu: theta(log n), caz defav: theta(n)
// sterge un element si reface legaturile (1: frunza, 2: 1 fiu, 3: 2 fii)
bool Multime::sterge(TElem elem) {
	Nod* curent = radacina;
	Nod* parinte = nullptr;

	// cautam nodul de sters
	while (curent != nullptr && curent->e != elem) {
		parinte = curent;
		if (rel(elem, curent->e)) {
			curent = curent->st;
		}
		else {
			curent = curent->dr;
		}
	}

	if (curent == nullptr) {
		return false; // nu am gasit
	}

	// cazul in care nodul are 2 fii: gasim succesorul (cel mai mic din subarborele drept)
	if (curent->st != nullptr && curent->dr != nullptr) {
		Nod* succesor = curent->dr;
		Nod* parinteSuccesor = curent;

		while (succesor->st != nullptr) {
			parinteSuccesor = succesor;
			succesor = succesor->st;
		}

		// mutam valoarea succesorului in nodul curent
		curent->e = succesor->e;

		// stergem succesorul (max 1 fiu pe dreapta)
		curent = succesor;
		parinte = parinteSuccesor;
	}

	// cazul in care nodul are 0 sau 1 fiu
	Nod* fiu = (curent->st != nullptr) ? curent->st : curent->dr;

	if (parinte == nullptr) {
		radacina = fiu; // stergem chiar radacina
	}
	else if (parinte->st == curent) {
		parinte->st = fiu;
	}
	else {
		parinte->dr = fiu;
	}

	delete curent;
	dimensiune--;
	return true;
}

// complexitate: caz fav: theta(1), caz med: theta(log n), caz defav: O(n)
// navigam stanga/dreapta folosind relatia pentru a cauta un nod.
bool Multime::cauta(TElem elem) const {
	Nod* curent = radacina;
	while (curent != nullptr) {
		if (curent->e == elem) {
			return true;
		}
		if (rel(elem, curent->e)) {
			curent = curent->st;
		}
		else {
			curent = curent->dr;
		}
	}
	return false;
}

// complexitate: theta(1)
int Multime::dim() const {
	return dimensiune;
}

// complexitate: theta(1)
bool Multime::vida() const {
	return dimensiune == 0;
}

// complexitate: theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

/*
// complexitate: O(n) - parcurgem intreg arborele in postordine
void Multime::distrugeRec(Nod* p) {
	if (p != nullptr) {
		distrugeRec(p->st);
		distrugeRec(p->dr);
		delete p;
	}
}
*/

// complexitate: O(n) - parcurgem si stergem iterativ stack overflow
void Multime::distrugeRec(Nod* p) {
	if (p == nullptr) {
		return;
	}

	std::stack<Nod*> s;
	s.push(p);

	while (!s.empty()) {
		Nod* curent = s.top();
		s.pop();

		// salvam pointerii catre copii in stiva inainte sa stergem nodul curent
		if (curent->st != nullptr) {
			s.push(curent->st);
		}
		if (curent->dr != nullptr) {
			s.push(curent->dr);
		}

		delete curent;
	}
}

Multime::~Multime() {
	distrugeRec(radacina);
}