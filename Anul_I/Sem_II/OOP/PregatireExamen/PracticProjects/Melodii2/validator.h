#pragma once
#include <string>
#include "domain.h"

//exceptii pt file/repo
class RepoException {
private:
	std::string mesaj;
public:
	RepoException(const std::string& mesaj) : mesaj{ mesaj } {}
	std::string getMesaj() const { return mesaj; }
};

//exceptii validarea datelor
class ValidException {
private:
	std::string mesaj;
public:
	ValidException(const std::string& mesaj) : mesaj{ mesaj } {}
	std::string getMesaj() const { return mesaj; }
};

//validare melodie
class ValidatorMelodie {
public:
	void valideaza(const Melodie& m) const {
		std::string erori = "";
		if (m.getId() < 0) erori += "Id nu poate fi negativ!\n";
		if (m.getTitlu().empty()) erori += "Titlul nu poate fi nul!\n";
		if (m.getGen().empty()) erori += "Genul nu poate fi nul!\n";
		if (m.getArtist().empty()) erori += "Artistul nu poate fi nul!\n";
		if ((m.getGen() != "pop")&&(m.getGen() != "rock") && (m.getGen() != "folk") && (m.getGen() != "disco")) erori += "Genul este unu dintre: pop, rock, folk, disco!\n";

		if (!erori.empty()) {
			throw ValidException(erori);
		}
	}
};