#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
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

	QLineEdit* editMarca;

	QPushButton* btnSortare;
	QPushButton* btnFiltrare;
	QPushButton* btnReset;

	void initGui();
	void connectSignals();
	void reloadTable(const std::vector<Masina>& masini);

public:
	MasiniGUI(ServiceMasini& srv);
};