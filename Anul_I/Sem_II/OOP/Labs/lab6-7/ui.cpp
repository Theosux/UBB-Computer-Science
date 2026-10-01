#include "ui.h"
#include <iostream>
#include <string>
#include "raport.h"
#include <unordered_map>

using std::cout;
using std::cin;

void ConsoleUI::printMenu() {
	cout << "\nMeniu: \n";
	cout << "1. Adauga locatar\n";
	cout << "2. Afiseaza toti locatarii\n";
	cout << "3. Sterge locatar\n";
	cout << "4. Modifica locatar\n";
	cout << "5. Cauta apartament\n";
	cout << "6. Filtrare\n";
	cout << "7. Sortare\n";
	cout << "8. Meniu lista de notificare\n";
	cout << "9. Raport tipuri apartamente\n";
	cout << "10. Undo\n";
	cout << "0. Iesire\n";
}

void ConsoleUI::meniuListaNotificare() {
	int cmd = -1;
	while (true) {
		cout << "\nMeniu Lista de Notificare: \n";
		cout << "1. Adauga apartament in lista\n";
		cout << "2. Goleste lista\n";
		cout << "3. Genereaza lista aleator\n";
		cout << "4. Exporta lista in fisier\n";
		cout << "0. Inapoi la meniul principal\n";
		cout << "Alege comanda: ";
		cin >> cmd;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}

		if (cmd == 0) break;

		try {
			if (cmd == 1) {
				int ap;
				cout << "Dati numarul apartamentului: ";
				cin >> ap;
				srv.adaugaInListaNotificare(ap);
			}
			else if (cmd == 2) {
				srv.golesteListaNotificare();
			}
			else if (cmd == 3) {
				int nr;
				cout << "Cate apartamente doriti sa adaugati? ";
				cin >> nr;
				srv.genereazaListaNotificare(nr);
			}
			else if (cmd == 4) {
				std::string numeFisier;
				cout << "Dati numele fisierului (ex: fisier.html sau fisier.csv): ";
				cin >> numeFisier;
				srv.exportaListaNotificare(numeFisier);
				cout << "Export realizat cu succes!\n";
			}
		}
		catch (const RepoException& ex) {
			cout << "Eroare: " << ex.getMesaj() << "\n";
		}

		cout << "Numar total de apartamente in lista de notificare: " << srv.getListaNotificare().size() << "\n";
	}
}

void ConsoleUI::afiseazaLista(const std::vector<Locatar>& locatari) {
	if (locatari.empty()) {
		cout << "\nNu exista niciun locatar care sa corespunda criteriilor!\n";
		return;
	}

	cout << "\nRezultate\n";
	for (const auto& l : locatari) {
		cout << "Ap: " << l.getApartament()
			<< " | Nume: " << l.getNumeProprietar()
			<< " | Suprafata(mp): " << l.getSuprafata()
			<< " | Tip: " << l.getTipApartament() << "\n";
	}
	cout << "\n\n";
}

void ConsoleUI::adaugaUI() {
	int apartament = -1, suprafata = -1;
	std::string nume, tip;

	cout << "Dati numarul apartamentului:";
	cin >> apartament;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	cin.ignore();
	
	cout << "Dati numele proprietarului:";
	std::getline(cin, nume);

	cout << "Dati suprafata:";
	cin >> suprafata;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	cin.ignore();

	cout << "Dati tipul apartamentului:";
	std::getline(cin, tip);

	try {
		srv.adaugaLocatar(apartament, nume, suprafata, tip);
		cout << "Locatar adaugat cu succes!\n";
	}
	catch (const ValidatorException& ex) {
		cout << "\n Eroare validare:\n" << ex.getErrorMsgs();
	}
	catch (const RepoException& ex) {
		cout << "\n Eroare de repo:\n" << ex.getMesaj() << "\n";
	}
}

void ConsoleUI::afiseazaUI() {
	const auto& locatari = srv.getAllLocatari();
	afiseazaLista(locatari);
}

void ConsoleUI::stergeUI() {
	int apartament;
	cout << "Dati numarul apartamentului pe care doriti sa il stergeti: ";
	cin >> apartament;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	try {
		srv.stergeLocatar(apartament);
		cout << "Locatar sters cu succes!\n";
	}
	catch (const RepoException& ex) {
		cout << "\n Eroare: " << ex.getMesaj() << "\n";
	}
}

void ConsoleUI::modificaUI() {
	int apartament = -1, suprafata = -1;
	std::string nume, tip;

	cout << "Dati nr apartamentului de modificat:";
	cin >> apartament;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	cin.ignore();

	cout << "Dati noul nume al proprietarului:";
	std::getline(cin, nume);

	cout << "Dati noua suprafata:";
	cin >> suprafata;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	cin.ignore();

	cout << "Dati noul tip de apartament:";
	std::getline(cin, tip);

	try {
		srv.modificaLocatar(apartament, nume, suprafata, tip);
		cout << "Locatar modificat.\n";
	}
	catch (const ValidatorException& ex) {
		cout << "\n Eroare validare:\n" << ex.getErrorMsgs();
	}
	catch (const RepoException& ex) {
		cout << "\n Eroare de repo:\n" << ex.getMesaj() << "\n";
	}
}

void ConsoleUI::cautaUI() {
	int apartament;
	cout << "Dati numarul apartamentului cautat: ";
	cin >> apartament;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	try {
#pragma warning(suppress: 26823)
		const auto& loc = srv.cautaApartament(apartament);
		cout << "\nLocatar gasit: Ap: " << loc.getApartament() << " | Nume: " << loc.getNumeProprietar() << " | Suprafata: " << loc.getSuprafata() << " | Tip: " << loc.getTipApartament() << "\n";
	}
	catch (const RepoException& ex) {
		cout << "\n Eroare: " << ex.getMesaj() << "\n";
	}
}

void ConsoleUI::filtreazaUI() {
	cout << "\n--- Filtrare ---\n";
	cout << "1. Dupa tip apartament\n";
	cout << "2. Dupa suprafata\n";
	cout << "Alegerea dumneavoastra: ";

	int optiune;
	cin >> optiune;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	if (optiune == 1) {
		std::string tip;
		cout << "Dati tipul dorit: ";
		cin.ignore();
		std::getline(cin, tip);
		afiseazaLista(srv.filtreazaDupaTip(tip));
	}
	else if (optiune == 2) {
		int suprafata;
		cout << "Dati suprafata dorita: ";
		cin >> suprafata;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Eroare: Trebuie introdus un numar!\n";
			return;
		}

		afiseazaLista(srv.filtreazaDupaSuprafata(suprafata));
	}
	else {
		cout << "Optiune invalida!\n";
	}
}

void ConsoleUI::sorteazaUI() {
	cout << "\n--- Sortare ---\n";
	cout << "1. Dupa Nume\n";
	cout << "2. Dupa Suprafata\n";
	cout << "3. Dupa Tip si Suprafata\n";
	cout << "Alegerea dumneavoastra: ";

	int optiune;
	cin >> optiune;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Eroare: Trebuie introdus un numar!\n";
		return;
	}

	if (optiune == 1) {
		afiseazaLista(srv.sorteazaDupaNume());
	}
	else if (optiune == 2) {
		afiseazaLista(srv.sorteazaDupaSuprafata());
	}
	else if (optiune == 3) {
		afiseazaLista(srv.sorteazaDupaTipSiSuprafata());
	}
	else {
		cout << "Optiune invalida!\n";
	}
}

void ConsoleUI::raportUI() {
	cout << "\nRaport tipuri apartamente\n";

	std::unordered_map<std::string, RaportDTO> raport = srv.getRaportTipuri();

	if (raport.empty()) {
		cout << "Nu exista locatari adaugati inca!\n";
		return;
	}

	// parcurgem mapu
	for (const auto& pereche : raport) {
		const RaportDTO& dto = pereche.second;

		cout << "Tip apartament: " << dto.getTip() << " -> " << dto.getCount() << " apartamente\n";
	}
	cout << "\n";
}

void ConsoleUI::start() {
	int cmd = -1;
	while (true) {
		printMenu();
		cout << "Introdu comanda:";
		cin >> cmd;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Eroare: Trebuie introdus un numar!\n";
			return;
		}

		if (cmd == 1) {
			adaugaUI();
		}
		else if (cmd == 2) {
			afiseazaUI();
		}
		else if (cmd == 3) {
			stergeUI();
		}
		else if (cmd == 4) {
			modificaUI();
		}
		else if (cmd == 5) {
			cautaUI();
		}
		else if (cmd == 6) {
			filtreazaUI();
		}
		else if (cmd == 7) {
			sorteazaUI();
		}
		else if (cmd == 8) {
			meniuListaNotificare();
		}
		else if (cmd == 9) {
			raportUI();
		}
		else if (cmd == 10) {
			try {
				srv.undo();
				cout << "Undo efectuat.\n";
			}
			catch (const RepoException& ex) {
				cout << "Eroare: " << ex.getMesaj() << "\n";
			}
		}
		else if (cmd == 0) {
			cout << "Aplicatia a fost inchisa.";
			break;
		}
		else {
			cout << "Comanda invalida \n";
		}
	}
}