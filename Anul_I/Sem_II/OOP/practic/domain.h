#pragma once
#include <string>

class Student {
private:
	int nrMatricol;
	std::string nume;
	int varsta;
	std::string facultate;
public:
	//constructor default
	Student() = default;
	//constructor init
	Student(int nrmatricol, const std::string& nume, int varsta, const std::string& facultate);

	//gettere
	int getNrMatricol() const;
	std::string getNume() const;
	int getVarsta() const;
	std::string getFacultate() const;

	//settere
	void setVarsta(int varsta);
};