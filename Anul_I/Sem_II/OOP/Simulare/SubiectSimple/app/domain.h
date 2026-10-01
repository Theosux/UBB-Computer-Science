#pragma once
#include <string>

class Masina {
private:
	int id;
	std::string marca;
	std::string model;
	int an;
public:
	Masina() = default;
	Masina(int id, const std::string& marca, const std::string& model, int an);

	//gettere
	int getId() const;
	std::string getMarca() const;
	std::string getModel() const;
	int getAn() const;
};