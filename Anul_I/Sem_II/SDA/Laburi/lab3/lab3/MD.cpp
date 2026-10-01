#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


MD::MD() {
	/* Theta(1) */

	this->prim = nullptr;
	this->ultim = nullptr;
	this->dimensiune = 0;
}


void MD::adauga(TCheie c, TValoare v) {
	/* O(n), unde n este nr de chei distincte */

	NodCheie* curent = this->prim;

	while (curent != nullptr && curent->cheie != c) {
		curent = curent->urm;
	}

	if (curent == nullptr) {
		curent = new NodCheie{ c, nullptr, nullptr, this->ultim, nullptr };
		if (this->ultim != nullptr) {
			this->ultim->urm = curent;
		}
		else {
			this->prim = curent;					// prima cheie din md
		}
		this->ultim = curent;
	}

	NodValoare* nodNouValoare = new NodValoare{ v, curent->ultimval, nullptr };
	if (curent->ultimval != nullptr) {
		curent->ultimval->urm = nodNouValoare;
	}
	else {
		curent->primval = nodNouValoare;			// e prima val pt aceasta cheie
	}
	curent->ultimval = nodNouValoare;
	
	this->dimensiune++;
}


bool MD::sterge(TCheie c, TValoare v) {
	/* O(n+m), n - nr chei, m - nr valori ale cheii */

	NodCheie* curent = this->prim;

	//cautam cheia
	while (curent != nullptr && curent->cheie != c) {
		curent = curent->urm;
	}
	if (curent == nullptr) return false;

	//cautam val
	NodValoare* valCurenta = curent->primval;
	while (valCurenta != nullptr && valCurenta->valoare != v) {
		valCurenta = valCurenta->urm;
	}
	if (valCurenta == nullptr) return false;

	if (valCurenta->prec != nullptr) valCurenta->prec->urm = valCurenta->urm;
	else curent->primval = valCurenta->urm;	// se sterge primul

	if (valCurenta->urm != nullptr) valCurenta->urm->prec = valCurenta->prec;
	else curent->ultimval = valCurenta->prec; // ultimul

	delete valCurenta;
	this->dimensiune--;

	if (curent->primval == nullptr) {
		if (curent->prec != nullptr) curent->prec->urm = curent->urm;
		else this->prim = curent->urm;

		if (curent->urm != nullptr) curent->urm->prec = curent->prec;
		else this->ultim = curent->prec;

		delete curent;
	}
	return true;
}


vector<TValoare> MD::cauta(TCheie c) const {
	/* O(n+m), n - nr chei, m - nr val de returnat */

	vector<TValoare> valori;
	NodCheie* curent = this->prim;

	while (curent != nullptr && curent->cheie != c) {
		curent = curent->urm;
	}

	if (curent != nullptr) {
		NodValoare* valCurenta = curent->primval;
		while (valCurenta != nullptr) {
			valori.push_back(valCurenta->valoare);
			valCurenta = valCurenta->urm;
		}
	}

	return valori;
}


int MD::dim() const {
	/* Theta(1) */

	return this->dimensiune;
}


bool MD::vid() const {
	/* Theta(1) */

	return this->dimensiune == 0;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	/* Theta(n), n - toate nodurile alocate */

	NodCheie* curentCheie = this->prim;
	while (curentCheie != nullptr) {
		NodValoare* curentValoare = curentCheie->primval;

		// dealocam toate valorile pentru cheia curenta
		while (curentValoare != nullptr) {
			NodValoare* valDeSters = curentValoare;
			curentValoare = curentValoare->urm;
			delete valDeSters;
		}

		// dealocam cheia
		NodCheie* cheieDeSters = curentCheie;
		curentCheie = curentCheie->urm;
		delete cheieDeSters;
	}
}

