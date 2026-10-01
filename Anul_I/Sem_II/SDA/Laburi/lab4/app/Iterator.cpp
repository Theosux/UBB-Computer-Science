#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
	curent = dict.prim;   
}

void Iterator::prim() { 
	curent = dict.prim;
}

void Iterator::urmator() {
	if (!valid()) {
		throw exception();
	}
	curent = dict.urm[curent];
}

bool Iterator::valid() const {
	return curent != -1;
}

TElem Iterator::element() const {
	if (!valid()) {
		throw exception();
	}
	return dict.e[curent];
}


