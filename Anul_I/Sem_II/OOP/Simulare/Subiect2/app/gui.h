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

class ParcAutoGUI : public QWidget {
private:
	ServiceMasini& srv;

	//comp vizuale
	QListWidget* lst;
	QTableWidget* table;

	//pt adaugare(formular):
	QLineEdit* editId;
	QLineEdit* editMarca;
	QLineEdit* editModel;
	QLineEdit* editPretZi;

	QPushButton* btnAdauga;
	QPushButton* btnSterge;
	QPushButton* btnInchiriaza;
	QPushButton* btnSortMarca;
	QPushButton* btnSortPret;
	QPushButton* btnFiltrareMarca;
	QPushButton* btnNesortat;

	//fct initializare si conectare
	void initGUI();
	void connectSignals();

	//fct reload
	void reloadList(const std::vector<Masina>& masini);

public:
	//constructor primeste srv
	ParcAutoGUI(ServiceMasini& srv);
};