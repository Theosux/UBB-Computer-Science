#include "tabel.h"
#include <QString>
#include <QColor>

int StudentTabelModel::rowCount(const QModelIndex&) const {
	return int(studenti.size());
}

int StudentTabelModel::columnCount(const QModelIndex&) const {
	return 4;
}

QVariant StudentTabelModel::data(const QModelIndex& index, int role) const {
	const Student& s = studenti[index.row()];

	//textul din celule
	if (role == Qt::DisplayRole) {
		int col = index.column();
		if (col == 0) return s.getNrMatricol();
		if (col == 1) return QString::fromStdString(s.getNume());
		if (col == 2) return s.getVarsta();
		if (col == 3) return QString::fromStdString(s.getFacultate());
		return QVariant{};
	}

	//colorare
	if (role == Qt::BackgroundRole) {
		std::string fac = s.getFacultate();
		if (fac == "mate") return QColor("red");
		if (fac == "info") return QColor("blue");
		if (fac == "mate-info") return QColor("purple");
		if (fac == "ai") return QColor("green");
		return QVariant{};
	}

	return QVariant{};
}

QVariant StudentTabelModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) {
		return QVariant{};
	}
	if (orientation == Qt::Horizontal) {
		if (section == 0) return "Nr Matricol";
		if (section == 1) return "Nume";
		if (section == 2) return "Varsta";
		if (section == 3) return "Facultate";
	}
	return QVariant{};
}

void StudentTabelModel::setStudenti(const std::vector<Student>& studentiNoi) {
	//reset model
	beginResetModel();
	studenti = studentiNoi;
	endResetModel();
}

Student StudentTabelModel::getStudentAt(int row) const {
	return studenti[row];
}