#include "tabel.h"
#include <QString>

int MelodiiTableModel::rowCount(const QModelIndex&) const {
	return int(melodii.size());
}

int MelodiiTableModel::columnCount(const QModelIndex&) const {
	return 5;
}

QVariant MelodiiTableModel::data(const QModelIndex& index, int role) const {
	if (role != Qt::DisplayRole) {
		return QVariant{};
	}
	const Melodie& m = melodii[index.row()];
	int col = index.column();

	if (col == 0) return m.getId();
	if (col == 1) return QString::fromStdString(m.getTitlu());
	if (col == 2) return QString::fromStdString(m.getArtist());
	if (col == 3) return m.getRank();
	if (col == 4) {
		//nr cate melodii au acelasi rank ca melodia curenta
		int nr = 0;
		for (const auto& alta : melodii) {
			if (alta.getRank() == m.getRank()) {
				nr++;
			}
		}
		return nr;
	}
	return QVariant{};
}

QVariant MelodiiTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) {
		return QVariant{};
	}
	if (orientation == Qt::Horizontal) {
		if (section == 0) return "ID";
		if (section == 1) return "Titlu";
		if (section == 2) return "Artist";
		if (section == 3) return "Rank";
		if (section == 4) return "Nr. melodii cu acelasi rank";
	}
	return QVariant{};
}

void MelodiiTableModel::setMelodii(const std::vector<Melodie>& melodiiNoi) {
	//reset model
	beginResetModel();
	melodii = melodiiNoi;
	endResetModel();
}

Melodie MelodiiTableModel::getMelodieAt(int row) const {
	return melodii[row];
}