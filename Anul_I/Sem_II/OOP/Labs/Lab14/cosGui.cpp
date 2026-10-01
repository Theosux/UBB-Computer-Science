#include "cosGui.h"

// implementare cosCRUDgui

CosCRUDGUI::CosCRUDGUI(LocatarService& srv) : srv{ srv } {
    initGUI();
    connectSignals();

    srv.addObserver(this); // abonare notificari
    update();              // update pt populare
}

CosCRUDGUI::~CosCRUDGUI() {
    srv.removeObserver(this); // dezabonare la distrugerea ferestrei
}

void CosCRUDGUI::initGUI() {
    QVBoxLayout* mainL = new QVBoxLayout(this);

    // Configurare View/Model
    table = new QTableView;
    model = new CosTableModel(this);
    table->setModel(model);
    mainL->addWidget(table);

    // Configurare butoane
    QHBoxLayout* btnL = new QHBoxLayout;
    editNumar = new QLineEdit;
    editNumar->setPlaceholderText("Nr. elemente...");
    btnGenereaza = new QPushButton("Genereaza");
    btnGoleste = new QPushButton("Goleste");

    btnL->addWidget(editNumar);
    btnL->addWidget(btnGenereaza);
    btnL->addWidget(btnGoleste);
    mainL->addLayout(btnL);
}

void CosCRUDGUI::connectSignals() {
    QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
        srv.golesteListaNotificare(); //notify in service
        });

    QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
        int nr = editNumar->text().toInt();
        srv.genereazaListaNotificare(nr); // notify in service
        });
}

void CosCRUDGUI::update() {
    model->setLocatari(srv.getListaNotificare());
}


// implementare cosREADonlygui

CosReadOnlyGUI::CosReadOnlyGUI(LocatarService& srv) : srv{ srv } {
    srv.addObserver(this);
    update();
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
    srv.removeObserver(this);
}

void CosReadOnlyGUI::update() {
    repaint(); // forteaza apelarea
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
    QPainter p{ this };
    int count = srv.getListaNotificare().size();

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> xDist(0, width() - 50);
    std::uniform_int_distribution<> yDist(0, height() - 50);

    for (int i = 0; i < count; i++) {
        int x = xDist(mt);
        int y = yDist(mt);

        p.setBrush(Qt::darkRed);
        p.drawRect(x, y, 40, 40); // patrat
    }
}