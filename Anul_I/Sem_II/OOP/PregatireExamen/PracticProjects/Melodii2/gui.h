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
#include <QPainter>
#include <QPaintEvent>
#include "service.h"
#include "tabel.h"

class MelodiiGUI : public QWidget {
private:
	ServiceMelodii& srv;

	//tabel custom
	QTableView* tableView;
	MelodiiTableModel* model;

	//zona modificare
	QLineEdit* adTitlu;
	QLineEdit* adArtist;
	QLineEdit* adGen;
	QPushButton* btnAdauga;
	QPushButton* btnDelete;

	void initGUI();
	void connectSignals();
	void reloadAll();

	//cerinta 5: deseneaza cercurile concentrice intr-un colt
	void deseneazaCercuri(QPainter& p, QPoint centru, int nrMelodii, QColor culoare);
protected:
	//cerinta 5: desenul din cele 4 colturi
	void paintEvent(QPaintEvent* ev) override;
public:
	MelodiiGUI(ServiceMelodii& srv);
};