#include "IteratorMultime.h"
#include "Multime.h"
#include <stdexcept>


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	curent = 0;
}


void IteratorMultime::prim() {
	curent = 0;
}


void IteratorMultime::urmator() {
	if (!valid()) {
		throw std::runtime_error("Iterator invalid");
	}
	curent++;
}


TElem IteratorMultime::element() const {
	if (!valid()) {
		throw std::runtime_error("Iterator invalid");
	}
	return multime.elemente[curent];
}

bool IteratorMultime::valid() const {
	return curent < multime.dimensiune;
}
