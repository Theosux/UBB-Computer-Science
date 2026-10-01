#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QString>
#include "service.h"
#include "tabel.h"

class StudentGUI : public QWidget {
private:
	ServiceStudent& srv;

	//model + view
	StudentTabelModel* model;
	QTableView* tableView;

	//butoane
	QPushButton* btnSterge;
	QPushButton* btnImbatranire;
	QPushButton* btnIntinerire;
	QPushButton* btnUndo;
	QPushButton* btnRedo;

	//constructie interfata
	void initGUI();
	void connectSignals();

	//reincarcarea datelor in tabel
	void reloadAll();

public:
	StudentGUI(ServiceStudent& srv);
};