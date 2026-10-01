#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <random>
#include "service.h"
#include "observer.h"
#include "CosTableModel.h" // modelul

// cosCRUDgui
class CosCRUDGUI : public QWidget, public Observer {
private:
    LocatarService& srv;
    QTableView* table;
    CosTableModel* model;
    QPushButton* btnGoleste;
    QPushButton* btnGenereaza;
    QLineEdit* editNumar;

    void initGUI();
    void connectSignals();

public:
    CosCRUDGUI(LocatarService& srv);
    ~CosCRUDGUI();
    void update() override;
};

// --- Fereastra 2: CosReadOnlyGUI ---
class CosReadOnlyGUI : public QWidget, public Observer {
private:
    LocatarService& srv;

public:
    CosReadOnlyGUI(LocatarService& srv);
    ~CosReadOnlyGUI();
    void update() override;

protected:
    void paintEvent(QPaintEvent* ev) override;
};