#pragma once
#include <string>
#include <vector>
#include "domain.h"

class ValidatorException {
private:
	std::vector<std::string> msgs;
public:
	ValidatorException(const std::vector<std::string>& errors);

	std::string getErrorMsgs() const;
};

class ValidatorLocatar {
public:
	void valideaza(const Locatar& l) const;
};