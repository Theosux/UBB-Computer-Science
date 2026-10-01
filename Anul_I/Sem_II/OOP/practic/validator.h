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

//validare student
class ValidatorStudent {
public:
	void valideaza(const Student& s) const {
		std::string erori = "";
		if (s.getNrMatricol() <= 0) erori += "Nr Matricol nu poate fi negativ sau nul!\n";
		if (s.getNume().empty()) erori += "Numele nu poate fi gol!\n";
		if (s.getVarsta() <= 0) erori += "Varsta nu poate fi negativa sau nula!\n";
		if ((s.getFacultate() != "mate") && (s.getFacultate() != "info") && (s.getFacultate() != "mate-info") && (s.getFacultate() != "ai")) erori += "Facultatea este una dintre: mate, info, mate-info, ai!\n";

		if (!erori.empty()) {
			throw ValidException(erori);
		}
	}
};