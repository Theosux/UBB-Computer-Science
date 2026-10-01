#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>



void IteratorColectie::deplasare() {
	// cat timp nu am term tabela si celula este fie 0(goala) fie -1(stearsa)
	while (curent < col.m && col.e[curent].frecv <= 0) {
		curent++;
	}
}

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = 0;
	frecvCurenta = 1;
	deplasare();
}

void IteratorColectie::prim() {
	// O(m)
	curent = 0;
	frecvCurenta = 1;
	deplasare();
}


void IteratorColectie::urmator() {
	if (!valid()) {
		throw std::exception();
	}
	// daca nu am term toate frecventele din el curent
	if (frecvCurenta < col.e[curent].frecv) {
		frecvCurenta++;
	}
	else {
		// trecem la urm element	
		curent++;
		frecvCurenta = 1;
		deplasare();
	}
}


bool IteratorColectie::valid() const {
	// theta(1)
	return curent < col.m;	
}



TElem IteratorColectie::element() const {
	// theta(1)
	if (!valid()) {
		throw std::exception();
	}
	return col.e[curent].elem;
}
