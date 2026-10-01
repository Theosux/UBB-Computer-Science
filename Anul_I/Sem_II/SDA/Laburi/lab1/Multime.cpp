#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>


void Multime::resize() {
	capacitate = capacitate * 2;
	TElem* elementeNoi = new TElem[capacitate];

	for (int i = 0; i < dimensiune; i++) {
		elementeNoi[i] = elemente[i];
	}

	delete[] elemente;

	elemente = elementeNoi;
}

Multime::Multime() {
	capacitate = 10;
	dimensiune = 0;
	elemente = new TElem[capacitate];
}


bool Multime::adauga(TElem elem) {
	if (cauta(elem)) {
		return false;
	}
	if (dimensiune == capacitate) {
		resize();
	}

	elemente[dimensiune] = elem;
	dimensiune++;

	return true;
}


bool Multime::sterge(TElem elem) {
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i] == elem) {
			elemente[i] = elemente[dimensiune - 1];				// Inlocuim cu ultimul element pt ca dim nu conteaza
			dimensiune--;
			return true;
		}
	}
	return false;												// Nu exista el daca se ajunge aici
}


bool Multime::cauta(TElem elem) const {
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i] == elem) {
			return true;
		}
	}
	return false;
}


int Multime::dim() const {
	return dimensiune;
}

bool Multime::vida() const {
	return dimensiune == 0;
}


Multime::~Multime() {
	delete[] elemente;
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

