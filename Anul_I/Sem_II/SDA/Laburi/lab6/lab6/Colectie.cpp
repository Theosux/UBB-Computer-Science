#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

int Colectie::hash(TElem elem) const {
	// theta(1)
	// +m pt nr negative
	int calc = elem % m;
	if (calc < 0) {
		calc += m;
	}
	return calc;
}

int Colectie::d(TElem elem, int i) const {
	// theta(1)
	// verificare patratica: d(c, i) = (hash(c) + 0.5*i + 0.5*i^2) % m
	long long i_long = i;
	return (hash(elem) + (i_long + i_long * i_long) / 2) % m;
}

void Colectie::redimensioneaza() {
	// theta(m) - nr elementelor dinaintea resize-ului
	int old_m = m;
	Pereche* old_e = e;

	m = m * 2; // dublam
	e = new Pereche[m];
	for (int i = 0; i < m; i++) {
		e[i].frecv = 0; // liber
	}

	// reinseram elementele valide
	for (int i = 0; i < old_m; i++) {
		if (old_e[i].frecv > 0) {
			int j = 0;
			int pos = d(old_e[i].elem, j);
			while (e[pos].frecv > 0) {
				j++;
				pos = d(old_e[i].elem, j);
			}
			e[pos] = old_e[i];
		}
	}
	delete[] old_e;
}

Colectie::Colectie() {
	m = 16;
	n = 0;
	distincte = 0;
	e = new Pereche[m];
	for (int i = 0; i < m; i++) {
		e[i].frecv = 0;
	}
}


void Colectie::adauga(TElem elem) {
	// AC: theta(1) (amortizat)
	// WC: O(m) - daca tabela este destul de plina sau daca se apeleaza redimensioneaza()
	int i = 0;
	int pos = d(elem, i);
	int prima_libera = -1;

	// cautam daca el exista
	while (i < m && e[pos].frecv != 0) {
		if (e[pos].elem == elem && e[pos].frecv > 0) {
			e[pos].frecv++; // incrementam frecventa
			n++;
			return;
		}
		if (e[pos].frecv == -1 && prima_libera == -1) {
			prima_libera = pos; // retinem prima celula stearsa
		}
		i++;
		pos = d(elem, i);
	}

	// daca e element nou verificam redimensionarea
	if (distincte + 1 >= 0.7 * m) {
		redimensioneaza();
		// tabela modificata, calculam poz curenta de inserare
		i = 0;
		pos = d(elem, i);
		while (i < m && e[pos].frecv > 0) { //-1 = inexistent
			i++;
			pos = d(elem, i);
		}
		prima_libera = -1;
	}

	// inserare
	int loc = (prima_libera != -1) ? prima_libera : pos;
	e[loc].elem = elem;
	e[loc].frecv = 1;
	n++;
	distincte++;
}


bool Colectie::sterge(TElem elem) {
	// AC: theta(1)
	// WC: O(m) - daca elementul nu exista insa poz initiala are -1
	int i = 0;
	int pos = d(elem, i);

	while (i < m && e[pos].frecv != 0) {
		if (e[pos].elem == elem && e[pos].frecv > 0) {
			e[pos].frecv--;
			n--;
			// daca frecv ajunge 0 marcam poz cu -1(stearsa)
			if (e[pos].frecv == 0) {
				e[pos].frecv = -1;
				distincte--;
			}
			return true;
		}
		i++;
		pos = d(elem, i);
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	// AC: theta(1)
	// WC: O(m) - daca elementul nu exista insa poz initiala are -1
	int i = 0;
	int pos = d(elem, i);

	while (i < m && e[pos].frecv != 0) {
		if (e[pos].elem == elem && e[pos].frecv > 0) {
			return true;
		}
		i++;
		pos = d(elem, i);
	}
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	// asemanator cauta
	int i = 0;
	int pos = d(elem, i);

	while (i < m && e[pos].frecv != 0) {
		if (e[pos].elem == elem && e[pos].frecv > 0) {
			return e[pos].frecv;
		}
		i++;
		pos = d(elem, i);
	}
	return 0;
}


int Colectie::dim() const {
	// theta(1)
	return n;
}


bool Colectie::vida() const {
	// theta(1)
	return n == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] e;
}


