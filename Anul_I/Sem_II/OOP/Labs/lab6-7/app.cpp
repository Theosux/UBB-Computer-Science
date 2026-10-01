#include "teste.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include "ui.h"
#include "gui.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[] ) {
	ruleazaToateTestele();

	/*
	if (_CrtDumpMemoryLeaks() == 0) {
		printf("Nu exista memory leakuri! \n\n");
	}
	else {
		printf("Memory leakuri!\n\n");
	} 
	*/
	QApplication app(argc, argv);
	std::cout << "1. Repo salvare fisier\n";
	std::cout << "2. Repo dictionar cu probabilitati.\n";
	std::cout << "Alege repo: ";
	int optRepo = 0;
	std::cin >> optRepo;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Invalid, folosim file repo.\n";
		optRepo = 1;
	}

	std::unique_ptr<RepoAbstract> repo;

	if (optRepo == 2) {
		double probabilitate;
		std::cout << "Introdu prob de eroare(0.1-0.9): ";
		std::cin >> probabilitate;

		repo = std::make_unique<LocatarRepoDict>(probabilitate);
		std::cout << "App a pornit cu RepoDict (probabilitate de eroare " << probabilitate << ")\n\n";
	}
	else {
		repo = std::make_unique<LocatarRepoFile>("locatari.txt");
		std::cout << "App a pornit cu RepoFile.\n\n";
	}

	ValidatorLocatar val;

	LocatarService srv{ *repo, val };

	/*
	ConsoleUI ui{ srv };
	ui.start();
	*/

	LocatarGUI gui{ srv };
	gui.setWindowTitle("Gestiune Locatari - GUI");
	gui.show();

	return app.exec();
}