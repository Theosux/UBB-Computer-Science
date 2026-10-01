#include "service.h"
#include "raport.h"
#include <algorithm>
#include <iterator>
#include <random>  
#include <fstream>
#include <unordered_map>

void LocatarService::adaugaLocatar(int apartament, const std::string& nume, int suprafata, const std::string& tip) {
	Locatar l{ apartament, nume, suprafata, tip };

	val.valideaza(l);
	repo.adauga(l);

	undoActions.push_back(std::make_unique<UndoAdauga>(repo, l));
}

void LocatarService::stergeLocatar(int apartament) {
	// *trb sa si gasim locatarul
	Locatar locatarDeSters = cautaApartament(apartament);
	repo.sterge(apartament);

	undoActions.push_back(std::make_unique<UndoSterge>(repo, locatarDeSters));
}

void LocatarService::modificaLocatar(int apartament, const std::string& numeNou, int suprafataNoua, const std::string& tipNou) {
	Locatar locatarNou{ apartament, numeNou, suprafataNoua, tipNou };
	val.valideaza(locatarNou);

	// *gasim locatarul vechi
	Locatar locatarVechi = cautaApartament(apartament);
	repo.modifica(locatarNou);

	undoActions.push_back(std::make_unique<UndoModifica>(repo, locatarVechi));
}

void LocatarService::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu mai exista actiuni pt undo.");
	}

	// ultima actiune
	ActiuneUndo* act = undoActions.back().get();
	if (act != nullptr) {
		act->doUndo();
	}

	undoActions.pop_back();
}

const std::vector<Locatar> LocatarService::getAllLocatari() const {
	return repo.getAll();
}

Locatar LocatarService::cautaApartament(int apartament) const {
	for (const auto& loc : repo.getAll()) {
		if (loc.getApartament() == apartament) {
			return loc; // Acum returneaza in siguranta o copie a obiectului
		}
	}
	throw RepoException("Nu exista locatar in acest apartament");
}

std::vector<Locatar> LocatarService::filtreazaDupaTip(const std::string& tip) const {
	std::vector<Locatar> rez;
	const auto all = repo.getAll();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [tip](const Locatar& loc) {
		return loc.getTipApartament() == tip;
		});
	return rez;
}

std::vector<Locatar> LocatarService::filtreazaDupaSuprafata(int suprafata) const {
	std::vector<Locatar> rez;
	const auto all = repo.getAll();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [suprafata](const Locatar& loc) noexcept {
		return loc.getSuprafata() == suprafata;
		});
	return rez;
}

std::vector<Locatar> LocatarService::sorteazaDupaNume() const {
	std::vector<Locatar> copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), [](const Locatar& l1, const Locatar& l2) {
		return l1.getNumeProprietar() < l2.getNumeProprietar();
		});
	return copie;
}

std::vector<Locatar> LocatarService::sorteazaDupaSuprafata() const {
	std::vector<Locatar> copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), [](const Locatar& l1, const Locatar& l2) noexcept {
		return l1.getSuprafata() < l2.getSuprafata();
		});
	return copie;
}

std::vector<Locatar> LocatarService::sorteazaDupaTipSiSuprafata() const {
	std::vector<Locatar> copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), [](const Locatar& l1, const Locatar& l2) {
		if (l1.getTipApartament() == l2.getTipApartament()) {
			return l1.getSuprafata() < l2.getSuprafata();
		}
		return l1.getTipApartament() < l2.getTipApartament();
		});
	return copie;
}

// LISTA NOTIFICARE

void LocatarService::golesteListaNotificare() noexcept {
	listaNotificare.clear();
	notify();//*		
}

void LocatarService::adaugaInListaNotificare(int apartament) {
	const auto& locatar = cautaApartament(apartament);
	listaNotificare.push_back(locatar);
	notify();//*
}

void LocatarService::genereazaListaNotificare(int numar) {
	const auto all = repo.getAll();
	if (all.empty()) return; // daca e gol nu avem ce adauga

	// generator aleator din C++11
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<size_t> dist(0, all.size() - 1);

	for (int i = 0; i < numar; i++) {
		const size_t indexAleator = dist(mt);
		listaNotificare.push_back(all.at(indexAleator));
	}
	notify();//*
}

const std::vector<Locatar>& LocatarService::getListaNotificare() const noexcept {
	return listaNotificare;
}

void LocatarService::stergeDinListaNotificare(int apartament) {
	auto it = std::find_if(listaNotificare.begin(), listaNotificare.end(), [apartament](const Locatar& l) {
		return l.getApartament() == apartament;
		});

	if (it == listaNotificare.end()) {
		throw RepoException("Locatarul nu este in lista de notificare!");
	}
	listaNotificare.erase(it);
	notify();
}

void LocatarService::exportaListaNotificare(const std::string& numeFisier) const {
	std::ofstream out(numeFisier);
	if (!out.is_open()) {
		throw RepoException("eroare deschidere!");
	}

	if (numeFisier.find(".html") != std::string::npos) {
		out << "<html><body>\n<h2>Lista de Notificare</h2>\n<ul>\n";
		for (const auto& l : listaNotificare) {
			out << "<li>Apartament " << l.getApartament() << ": " << l.getNumeProprietar() << "</li>\n";
		}
		out << "</ul>\n</body></html>\n";
	}
	else {
		// default csv
		out << "Apartament,NumeProprietar,Suprafata,TipApartament\n";
		for (const auto& l : listaNotificare) {
			out << l.getApartament() << "," << l.getNumeProprietar() << ","
				<< l.getSuprafata() << "," << l.getTipApartament() << "\n";
		}
	}
	out.close();
}

std::unordered_map<std::string, RaportDTO> LocatarService::getRaportTipuri() const {
	// calculam frecv
	std::unordered_map<std::string, int> frecvente;
	for (const auto& loc : repo.getAll()) {
		frecvente[loc.getTipApartament()]++;
	}

	std::unordered_map<std::string, RaportDTO> raport;
	for (const auto& pereche : frecvente) {
		// first e cheia (tipul)
		raport.insert({ pereche.first, RaportDTO(pereche.first, pereche.second) });
	}

	return raport;
}