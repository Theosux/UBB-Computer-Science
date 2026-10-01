#include "service.h"
#include <algorithm>

std::vector<Student> ServiceStudent::getAll() {
	return repo.getAll();
}

void ServiceStudent::stergereStudent(int nrMatricol) {
	istoric.push_back(repo.getAll()); //salvam vechea stare
	repo.sterge(nrMatricol);

}

std::vector<Student> ServiceStudent::getAllSortatiVarsta() {
	std::vector<Student> copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), [](const Student& a, const Student& b) {
		return a.getVarsta() < b.getVarsta();	//sortare cresc
		});
	return copie;
}

void ServiceStudent::imbatranire() {
	istoric.push_back(repo.getAll());
	repo.imbatranire();
}

void ServiceStudent::intinerire() {
	istoric.push_back(repo.getAll());
	repo.intinerire();
}

void ServiceStudent::undo() {
	istoricUndo.push_back(repo.getAll());
	if (istoric.empty()) {
		throw ValidException("Nu se mai poate da undo!");
	}
	repo.setAll(istoric.back());	//ultima salvare
	istoric.pop_back();
}

void ServiceStudent::redo() {
	if (istoricUndo.empty()) {
		throw ValidException("Nu se mai poate da redo!");
	}
	repo.setAll(istoricUndo.back());	//ultima salvare
	istoricUndo.pop_back();
}