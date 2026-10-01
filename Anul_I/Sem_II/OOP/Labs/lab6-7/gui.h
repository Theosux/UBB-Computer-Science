#pragma once
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "service.h"

// fereastra notif
class NotificareGUI : public QWidget {
private:
    LocatarService& srv;
    QListWidget* lstNotificari;
    QPushButton* btnGoleste;
    QPushButton* btnGenereaza;
    QLineEdit* editNumarGenereaza;
    QLineEdit* editNumeFisierExport;            //*
    QPushButton* btnExport;                     //*

    void initGUI();
    void connectSignals();
    void reloadList();

public:
    NotificareGUI(LocatarService& srv);
    void actualizeaza();
};

// fereastra principala
class LocatarGUI : public QWidget {
private:
    LocatarService& srv;

    // componente vizuale
    QListWidget* lst;
    QTableWidget* table;            // init tabel
    QLineEdit* editApartament;
    QLineEdit* editNume;
    QLineEdit* editSuprafata;
    QLineEdit* editTip;

    // lista tipuri
    QWidget* panelBtnsTip;
    QVBoxLayout* layoutBtnsTip;

    // butoane
    QPushButton* btnAdauga;
    QPushButton* btnSterge;
    QPushButton* btnModifica;
    QPushButton* btnUndo;
    QPushButton* btnSortNume;
    QPushButton* btnSortSuprafata;
    QPushButton* btnSortTipSuprafata;
    QPushButton* btnFiltruTip;
    QPushButton* btnFiltruSuprafata;
    QPushButton* btnAfiseazaToti;
    QPushButton* btnFereastraNotificari;
    QPushButton* btnAdaugaNotificare;
    QPushButton* btnCauta;                              //*

    // observer
    QPushButton* btnGolesteCos;
    QPushButton* btnGenereazaCos;
    QLineEdit* editGenerareCos;

    QPushButton* btnDeschideCosCRUD;
    QPushButton* btnDeschideCosReadOnly;
    // *

    // fereastra secundara
    NotificareGUI* fereastraNotificari;

    void initGUI();
    void connectSignals();
    void reloadList(const std::vector<Locatar>& locatari);

public:
    LocatarGUI(LocatarService& srv);
};