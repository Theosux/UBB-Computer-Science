#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <vector>

class CosTableModel : public QAbstractTableModel {
private:
    std::vector<Locatar> locatari;
public:
    CosTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setLocatari(const std::vector<Locatar>& noiLocatari) {
        beginResetModel();
        locatari = noiLocatari;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return locatari.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4; // apartament, nume, tip, suprafata
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const auto& l = locatari[index.row()];
            switch (index.column()) {
            case 0: return QString::number(l.getApartament());
            case 1: return QString::fromStdString(l.getNumeProprietar());
            case 2: return QString::number(l.getSuprafata());
            case 3: return QString::fromStdString(l.getTipApartament());
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "Apartament";
            case 1: return "Nume";
            case 2: return "Suprafata";
            case 3: return "Tip";
            }
        }
        return QVariant();
    }
};