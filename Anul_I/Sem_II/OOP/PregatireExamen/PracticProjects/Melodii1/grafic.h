#pragma once
#include <QWidget>
#include <vector>
#include "domain.h"

class GraficMelodii : public QWidget {
private:
	std::vector<Melodie> melodii;

protected:
	//metoda apelata automat de Qt cand trebuie redesenat
	void paintEvent(QPaintEvent* ev) override;

public:
	GraficMelodii(QWidget* parent = nullptr);

	//actualizeaza datele si cere redesenarea
	void setMelodii(const std::vector<Melodie>& melodiiNoi);
};