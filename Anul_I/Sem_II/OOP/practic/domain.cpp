#include "domain.h"

Student::Student(int nrMatricol, const std::string& nume, int varsta, const std::string& facultate)
	: nrMatricol{ nrMatricol }, nume{ nume }, varsta{ varsta }, facultate{ facultate } { }


//gettere
int Student::getNrMatricol() const {
	return nrMatricol;
}

std::string Student::getNume() const {
	return nume;
}

int Student::getVarsta() const {
	return varsta;
}

std::string Student::getFacultate() const {
	return facultate;
}

//settere
void Student::setVarsta(int varsta) {
	this->varsta = varsta;
}