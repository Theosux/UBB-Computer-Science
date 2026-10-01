#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	prim();
}

TElem IteratorMD::element() const{
	/* Theta(1) */

	if (!valid()) {
		throw exception();
	}
	return pair <TCheie, TValoare>(this->curentCheie->cheie, this->curentValoare->valoare);
}

bool IteratorMD::valid() const {
	/* Theta(1) */

	return this->curentCheie != nullptr && this->curentValoare != nullptr;
}

void IteratorMD::urmator() {
	/* Theta(1) */

	if (!valid()) {
		throw exception();
	}

	// daca mai avem val pt cheia curenta, mergem la urm val
	if (this->curentValoare->urm != nullptr) {
		this->curentValoare = this->curentValoare->urm;
	}
	else {
		// am epuizat valorile, mergem la urm cheie
		this->curentCheie = this->curentCheie->urm;
		if (this->curentCheie != nullptr) {
			this->curentValoare = this->curentCheie->primval;
		}
		else {
			this->curentValoare = nullptr;
		}
	}
}

void IteratorMD::prim() {
	/* Theta(1) */

	this->curentCheie = md.prim;
	if (this->curentCheie != nullptr) {
		this->curentValoare = this->curentCheie->primval;
	}
	else {
		this->curentValoare = nullptr;
	}
}

