#include "validator.h"

ValidatorException::ValidatorException(const std::vector<std::string>& errors) : msgs{ errors } {

}

std::string ValidatorException::getErrorMsgs() const {
	std::string fullMsg = "";
	for (const auto& msg : msgs) {
		fullMsg += msg + "\n";
	}
	return fullMsg;
}

void ValidatorLocatar::valideaza(const Locatar& l) const {
	std::vector<std::string> errors;
	if (l.getApartament() <= 0) {
		errors.push_back("Numarul apartamentului trebuie sa fie strict pozitiv");
	}
	if (l.getNumeProprietar().empty()) {
		errors.push_back("Numele proprietarului nu poate fi vid");
	}
	if (l.getSuprafata() <= 0) {
		errors.push_back("Suprafata trebuie sa fie strict pozitiva");
	}
	if (l.getTipApartament().empty()) {
		errors.push_back("Tipul apartamentului nu poate fi vid");
	}

	if (!errors.empty()) {
		throw ValidatorException(errors);
	}
}