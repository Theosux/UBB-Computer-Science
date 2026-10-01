#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "service.h"

class MagazinGUI : public QWidget {
private:
	ServiceRochii& srv;

	// comp vizuale

	QListWidget* lst;
	QTableWidget* table;
	
	// pt adaugare(formular)	:
	QLineEdit* editCod;
	QLineEdit* editDenumire;
	QLineEdit* editMarime;
	QLineEdit* editPret;
	
	QPushButton* btnAdauga;
	QPushButton* btnInchiriaza;
	QPushButton* btnSortMarime;
	QPushButton* btnSortPret;
	QPushButton* btnNesortat;
	QPushButton* btnSterge;		// stergere

	// fct initializare si conectare
	void initGUI();
	void connectSignals();

	// fct reload
	void reloadList(const std::vector<Rochie>& rochii);

public:
	// constructor primeste srv
	MagazinGUI(ServiceRochii& srv);
};