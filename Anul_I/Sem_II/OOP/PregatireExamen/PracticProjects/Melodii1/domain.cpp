#include "domain.h"

Melodie::Melodie(int id, const std::string& titlu, const std::string& artist, int rank)
	: id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } { }

//gettere
int Melodie::getId() const {
	return id;
}

std::string Melodie::getTitlu() const {
	return titlu;
}

std::string Melodie::getArtist() const {
	return artist;
}

int Melodie::getRank() const {
	return rank;
}