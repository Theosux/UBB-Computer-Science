#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFormLayout>
#include <QLineEdit>
#include "service.h"

class MasiniGUI : public QWidget {
private:
	ServiceMasini& srv;
	
	QTableWidget* table;

	//formular ca sa putem introduce apa pt filtrare
	QLineEdit* formApa;

	//cele 3 butoane pt sortare filtrare si reset
	QPushButton* btnSortare;
	QPushButton* btnFiltrare;
	QPushButton* btnReset;

	//functiile private gui
	void initGui();
	void connectSignals();
	void reloadTable(const std::vector<Masina>& masini);
public:
	MasiniGUI(ServiceMasini& srv); // constructorul preia direct serviceul
};