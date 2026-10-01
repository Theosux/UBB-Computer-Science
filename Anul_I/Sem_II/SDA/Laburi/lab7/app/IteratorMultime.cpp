#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

// complexitate: O(h) - h este inaltimea arborelui (datorita apelului functiei prim)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	prim();
}

// complexitate: caz fav: theta(1), caz mediu: O(h)
// coboara cat mai la stanga posibil de la radacina pentru a gasi primul element in inordine.
void IteratorMultime::prim() {
	// golim
	while (!stiva.empty()) {
		stiva.pop();
	}

	Multime::Nod* p = mult.radacina;
	while (p != nullptr) {	//coboram maxim dreapta
		stiva.push(p);
		p = p->st;
	}

	if (!stiva.empty()) {
		curent = stiva.top();
	}
	else {
		curent = nullptr;
	}
}

// complexitate: theta(1)
// returneaza elementul curent daca iteratorul e valid
TElem IteratorMultime::element() const {
	if (!valid()) {
		throw std::exception(); // exceptie
	}
	return curent->e;
}

// complexitate: theta(1)
bool IteratorMultime::valid() const {
	return curent != nullptr;
}

// complexitate: caz fav: theta(1), caz defav: theta(h), amortizat: theta(1)
// trece la urmatorul nod in inordine: scoatem din stiva si adaugam coborand pe stanga subarborelui drept
void IteratorMultime::urmator() {
	if (!valid()) {
		throw std::exception();
	}

	Multime::Nod* p = stiva.top();
	stiva.pop();

	if (p->dr != nullptr) {
		p = p->dr;
		while (p != nullptr) {
			stiva.push(p);
			p = p->st;
		}
	}

	if (!stiva.empty()) {
		curent = stiva.top();
	}
	else {
		curent = nullptr;
	}
}