#include "domain.h"

Melodie::Melodie(int id, const std::string& titlu, const std::string& artist, const std::string& gen)
	: id{ id }, titlu{ titlu }, artist{ artist }, gen { gen } { }

//gettere
int Melodie::getId() const {
	return id;
}

std::string Melodie::getTitlu() const {
	return titlu;
}

std::string Melodie::getGen() const {
	return gen;
}

std::string Melodie::getArtist() const {
	return artist;
}