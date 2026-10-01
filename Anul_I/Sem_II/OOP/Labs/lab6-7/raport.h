#pragma once
#include <string>

class RaportDTO {
private:
	std::string tip;
	int count;
public:
	RaportDTO(const std::string& tip, int count) noexcept : tip{ tip }, count{ count } {}

	std::string getTip() const {
		return tip;
	}

	int getCount() const noexcept {
		return count;
	}
};