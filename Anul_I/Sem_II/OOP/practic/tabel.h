#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "domain.h"

class StudentTabelModel : public QAbstractTableModel {
private:
	std::vector<Student> studenti;
public:
	//nr randuri = nr studenti
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	//4 coloane
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	//celulele
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	//antetul coloanelor
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	//reincarcare date tabel
	void setStudenti(const std::vector<Student>& studentiNoi);

	//student de pe un anumit rand(selectie)
	Student getStudentAt(int row) const;
};