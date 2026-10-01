#pragma once
#include "service.h"

class ConsoleUI {
private:
	LocatarService& srv;

	void adaugaUI();
	void afiseazaUI();
	void printMenu();
	void stergeUI();
	void modificaUI();
	void afiseazaLista(const std::vector<Locatar>& locatari);
	void cautaUI();
	void filtreazaUI();
	void sorteazaUI();
	void meniuListaNotificare();
	void raportUI();

public:
	ConsoleUI(LocatarService& srv) noexcept : srv{ srv } {} 
	ConsoleUI(const ConsoleUI& ot) = delete;

	void start();
};