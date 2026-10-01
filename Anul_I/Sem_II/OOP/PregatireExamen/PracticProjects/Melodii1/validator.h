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
		if (m.getArtist().empty()) erori += "Artistul nu poate fi nul!\n";
		if (m.getRank() < 0 || m.getRank() > 10) erori += "Rank trb sa fie de la 0 la 10\n";

		if (!erori.empty()) {
			throw ValidException(erori);
		}
	}
};