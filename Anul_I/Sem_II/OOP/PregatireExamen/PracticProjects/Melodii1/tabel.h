#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "domain.h"

class MelodiiTableModel : public QAbstractTableModel {
private:
	std::vector<Melodie> melodii;
public:
	//nr randuri == nr melodii
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	
	//5 coloane: id, titlu, artist, rank, nr melodii cu acelasi rank
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	
	//celule
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	
	//antetul coloanelor
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	
	//reincare date tabel
	void setMelodii(const std::vector<Melodie>& melodiiNoi);
	//melodia de pe un anumit rand(selectie)
	Melodie getMelodieAt(int row) const;
};