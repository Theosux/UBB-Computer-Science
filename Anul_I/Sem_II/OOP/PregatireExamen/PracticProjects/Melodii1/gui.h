#pragma once
#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QItemSelectionModel>
#include "service.h"
#include "tabel.h"
#include "grafic.h"

class MelodiiGUI : public QWidget {
private:
	ServiceMelodii& srv;

	//tabelul custom
	QTableView* tableView;
	MelodiiTableModel* model;

	//zona modificare
	QLineEdit* editTitlu;
	QSlider* sliderRank;
	QLabel* lblRank;
	QPushButton* btnUpdate;
	QPushButton* btnDelete;

	//graficul cu bare
	GraficMelodii* grafic;

	void initGUI();
	void connectSignals();
	void reloadAll();

public:
	MelodiiGUI(ServiceMelodii& srv);
};