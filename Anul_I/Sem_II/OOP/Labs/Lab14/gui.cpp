#include "gui.h"
#include "cosGui.h"
#include <QString>
#include <string>
#include <map>

// fereastra principala

LocatarGUI::LocatarGUI(LocatarService& srv) : srv{ srv } {
    initGUI();
    connectSignals();
    reloadList(srv.getAllLocatari());
    fereastraNotificari = new NotificareGUI(srv);
}

void LocatarGUI::initGUI() {
    // layout principal - lista in stanga butoanele in dreapta
    QHBoxLayout* mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    // in stanga, un nou layout
    QVBoxLayout* layoutStanga = new QVBoxLayout;

    // lista
    lst = new QListWidget;
    layoutStanga->addWidget(lst);

    // Tabelul
    table = new QTableWidget(0, 5);
    QStringList headerLabels;
    headerLabels << "Apartament" << "Nume" << "Suprafata" << "Tip";
    table->setHorizontalHeaderLabels(headerLabels);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    layoutStanga->addWidget(table);

    //add la layout principal
    mainLayout->addLayout(layoutStanga);


    // partea functionala
    QVBoxLayout* dreaptaLayout = new QVBoxLayout;

    // formular
    QFormLayout* formLayout = new QFormLayout;
    editApartament = new QLineEdit;
    editNume = new QLineEdit;
    editSuprafata = new QLineEdit;
    editTip = new QLineEdit;

    formLayout->addRow("Apartament:", editApartament);
    formLayout->addRow("Nume:", editNume);
    formLayout->addRow("Suprafata:", editSuprafata);
    formLayout->addRow("Tip:", editTip);

    dreaptaLayout->addLayout(formLayout);

    // zona lista tip
    panelBtnsTip = new QWidget;
    layoutBtnsTip = new QVBoxLayout;
    panelBtnsTip->setLayout(layoutBtnsTip);
    dreaptaLayout->addWidget(panelBtnsTip);

    // butoane
    QHBoxLayout* butoaneLayout = new QHBoxLayout;
    btnAdauga = new QPushButton("Adauga", this);
    btnSterge = new QPushButton("Sterge", this);
    btnModifica = new QPushButton("Modifica", this);
    btnUndo = new QPushButton("Undo", this);
    btnAdaugaNotificare = new QPushButton("Adauga in Notificari", this);
    btnCauta = new QPushButton("Cauta", this);              //*


    butoaneLayout->addWidget(btnAdauga);    // x
    butoaneLayout->addWidget(btnSterge);    // x
    butoaneLayout->addWidget(btnModifica);  // x
    butoaneLayout->addWidget(btnUndo);      // x
    butoaneLayout->addWidget(btnAdaugaNotificare);
    dreaptaLayout->addLayout(butoaneLayout);

    butoaneLayout->addWidget(btnCauta);                     //*

    // sortari
    QHBoxLayout* sortLayout = new QHBoxLayout;
    btnSortNume = new QPushButton("Sortare Nume");
    btnSortSuprafata = new QPushButton("Sortare Suprafata");
    btnSortTipSuprafata = new QPushButton("Sortare Tip + Suprafata");
    sortLayout->addWidget(btnSortTipSuprafata);
    sortLayout->addWidget(btnSortNume);
    sortLayout->addWidget(btnSortSuprafata);
    dreaptaLayout->addLayout(sortLayout);

    // filtrari
    QHBoxLayout* filtruLayout = new QHBoxLayout;
    btnFiltruTip = new QPushButton("Filtru Tip");
    btnFiltruSuprafata = new QPushButton("Filtru Suprafata");
    filtruLayout->addWidget(btnFiltruTip);
    filtruLayout->addWidget(btnFiltruSuprafata);
    dreaptaLayout->addLayout(filtruLayout);

    // reset
    btnAfiseazaToti = new QPushButton("Afiseaza Toti Locatarii");
    dreaptaLayout->addWidget(btnAfiseazaToti);

    // fereastra de notificari
    btnFereastraNotificari = new QPushButton("Deschide Meniu Notificari");
    dreaptaLayout->addWidget(btnFereastraNotificari);

    // cos(observer)
    btnAddOneToCos = new QPushButton("Adauga Locatar in Cos");
    btnRemoveOneFromCos = new QPushButton("Sterge Locatar din Cos");
    btnGolesteCos = new QPushButton("Goleste Cosul", this);
    dreaptaLayout->addWidget(btnGolesteCos);
    dreaptaLayout->addWidget(btnAddOneToCos);
    dreaptaLayout->addWidget(btnRemoveOneFromCos);

    QHBoxLayout* genCosLayout = new QHBoxLayout;
    editGenerareCos = new QLineEdit;
    editGenerareCos->setPlaceholderText("Nr. locatari...");
    btnGenereazaCos = new QPushButton("Genereaza Cos", this);
    genCosLayout->addWidget(editGenerareCos);
    genCosLayout->addWidget(btnGenereazaCos);
    dreaptaLayout->addLayout(genCosLayout);

    btnDeschideCosCRUD = new QPushButton("Deschide Cos (CRUD GUI)", this);
    btnDeschideCosReadOnly = new QPushButton("Deschide Cos (ReadOnly GUI)", this);
    dreaptaLayout->addWidget(btnDeschideCosCRUD);
    dreaptaLayout->addWidget(btnDeschideCosReadOnly);

    mainLayout->addLayout(dreaptaLayout);
}

void LocatarGUI::connectSignals() {
    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        if (lst->selectedItems().isEmpty()) {
            editApartament->setText("");
            editNume->setText("");
            editSuprafata->setText("");
            editTip->setText("");
            return;
        }
        QListWidgetItem* selItem = lst->selectedItems().at(0);
        QString text = selItem->text();
        QStringList parts = text.split(" | ");
        if (parts.size() == 4) {
            editApartament->setText(parts[0].split(": ")[1]);
            editNume->setText(parts[1].split(": ")[1]);
            editSuprafata->setText(parts[2].split(": ")[1]);
            editTip->setText(parts[3].split(": ")[1]);
        }
        });

    // conectare selectie tabel
    QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
        if (table->selectedItems().isEmpty()) {
            editApartament->setText("");
            editNume->setText("");
            editSuprafata->setText("");
            editTip->setText("");
            return;
        }
        // nr randului selectat
        int row = table->selectedItems().at(0)->row();
        // extragere text
        editApartament->setText(table->item(row, 0)->text());
        editNume->setText(table->item(row, 1)->text());
        editSuprafata->setText(table->item(row, 2)->text());
        editTip->setText(table->item(row, 3)->text());
        });

    // buton adaugare
    QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
        if (!editApartament || !editNume || !editSuprafata || !editTip) return;
        try {
            int ap = editApartament->text().toInt();
            std::string nume = editNume->text().toStdString();
            int supr = editSuprafata->text().toInt();
            std::string tip = editTip->text().toStdString();

            srv.adaugaLocatar(ap, nume, supr, tip);
            reloadList(srv.getAllLocatari());
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare Repo", QString::fromStdString(ex.getMesaj()));
        }
        catch (const ValidatorException& ex) {
            QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(ex.getErrorMsgs()));
        }
        });

    // buton stergere
    QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
        try {
            int ap = editApartament->text().toInt();
            srv.stergeLocatar(ap);
            reloadList(srv.getAllLocatari());
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
        });

    // buton modifica
    QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
        try {
            int ap = editApartament->text().toInt();
            std::string nume = editNume->text().toStdString();
            int supr = editSuprafata->text().toInt();
            std::string tip = editTip->text().toStdString();

            srv.modificaLocatar(ap, nume, supr, tip);
            reloadList(srv.getAllLocatari());
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
        catch (const ValidatorException& ex) {
            QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(ex.getErrorMsgs()));
        }
        });

    // buton adaugare notif
    QObject::connect(btnAdaugaNotificare, &QPushButton::clicked, [&]() {
        bool ok;
        int ap = editApartament->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Eroare", "Alege un apartament valid!");
            return;
        }
        try {
            srv.adaugaInListaNotificare(ap);
            fereastraNotificari->actualizeaza(); // ca sa se vada imediat si in lista secunadara
            QMessageBox::information(this, "Succes", "Adaugat in lista de notificari!");
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
        });


    // buton undo
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            srv.undo();
            reloadList(srv.getAllLocatari());
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
        });

    // sortari
    QObject::connect(btnSortNume, &QPushButton::clicked, [&]() {
        reloadList(srv.sorteazaDupaNume());
        });

    QObject::connect(btnSortTipSuprafata, &QPushButton::clicked, [&]() {
        reloadList(srv.sorteazaDupaTipSiSuprafata());
        });

    QObject::connect(btnSortSuprafata, &QPushButton::clicked, [&]() {
        reloadList(srv.sorteazaDupaSuprafata());
        });

    // resetare
    QObject::connect(btnAfiseazaToti, &QPushButton::clicked, [&]() {
        reloadList(srv.getAllLocatari());
        });

    // filtrari
    QObject::connect(btnFiltruTip, &QPushButton::clicked, [&]() {
        std::string tipCautat = editTip->text().toStdString();
        if (tipCautat.empty()) {
            QMessageBox::warning(this, "Eroare", "Umple casuta 'Tip' pentru filtrare");
            return;
        }
        reloadList(srv.filtreazaDupaTip(tipCautat));
        });

    QObject::connect(btnFiltruSuprafata, &QPushButton::clicked, [&]() {
        bool ok;
        int suprafataCautata = editSuprafata->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Eroare", "Umple casuta 'Suprafata' pentru filtrare!");
            return;
        }
        reloadList(srv.filtreazaDupaSuprafata(suprafataCautata));
        });


    // buton fereastra notificari
    QObject::connect(btnFereastraNotificari, &QPushButton::clicked, [&]() {
        fereastraNotificari->actualizeaza();
        fereastraNotificari->show();
        });


    // buton cautare
    QObject::connect(btnCauta, &QPushButton::clicked, [&]() {
        bool ok;
        int ap = editApartament->text().toInt(&ok);

        if (!ok) {
            QMessageBox::warning(this, "Eroare", "Introdu un nr valid de apartament pt cautare!");
            return;
        }

        try {
            // apel srv
            Locatar loc = srv.cautaApartament(ap);

            // afisare pop up
            QMessageBox::information(this, "Locatar Gasit",
                QString("Proprietar: %1\nSuprafata: %2\nTip: %3")
                .arg(QString::fromStdString(loc.getNumeProprietar()))
                .arg(loc.getSuprafata())
                .arg(QString::fromStdString(loc.getTipApartament())));
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
        });

    // observer
    // adaugare
    QObject::connect(btnAddOneToCos, &QPushButton::clicked, [&]() {
        try {
            int ap = editApartament->text().toInt();
            srv.adaugaInListaNotificare(ap);
            QMessageBox::information(this, "Succes", "Locatar adaugat in cos!");
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
        });

    // stergere
    QObject::connect(btnRemoveOneFromCos, &QPushButton::clicked, [&]() {
        try {
            int ap = editApartament->text().toInt();
            srv.stergeDinListaNotificare(ap);
            QMessageBox::information(this, "Succes", "Locatar sters din cos!");
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
    });

    // golire cos
    QObject::connect(btnGolesteCos, &QPushButton::clicked, [&]() {
        srv.golesteListaNotificare();
        QMessageBox::information(this, "Succes", "Cosul a fost golit!");
        });

    // generare cos
    QObject::connect(btnGenereazaCos, &QPushButton::clicked, [&]() {
        bool ok;
        int nr = editGenerareCos->text().toInt(&ok);
        if (!ok || nr <= 0) {
            QMessageBox::warning(this, "Eroare", "Introdu un numar valid!");
            return;
        }
        srv.genereazaListaNotificare(nr);
        QMessageBox::information(this, "Succes", QString("Au fost generati %1 locatari in cos!").arg(nr));
        });

    // deschidere fereastra crud
    QObject::connect(btnDeschideCosCRUD, &QPushButton::clicked, [&]() {
        auto* fereastraCRUD = new CosCRUDGUI(srv);
        fereastraCRUD->show();
        });

    // deschidere fereastra readonly
    QObject::connect(btnDeschideCosReadOnly, &QPushButton::clicked, [&]() {
        auto* fereastraReadOnly = new CosReadOnlyGUI(srv);
        fereastraReadOnly->show();
        });
}

void LocatarGUI::reloadList(const std::vector<Locatar>& locatari) {
    lst->clear();

    // golire tabel
    table->clearContents();
    table->setRowCount(static_cast<int>(locatari.size()));  // am folosit static cast pt warning

    int row = 0;

    for (const auto& l : locatari) {
        // popularea lista
        QString itemText = QString("Ap: %1 | Nume: %2 | Suprafata: %3 | Tip: %4")
            .arg(l.getApartament())
            .arg(QString::fromStdString(l.getNumeProprietar()))
            .arg(l.getSuprafata())
            .arg(QString::fromStdString(l.getTipApartament()));
        lst->addItem(itemText);

        // populare tabel
        table->setItem(row, 0, new QTableWidgetItem(QString::number(l.getApartament())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(l.getNumeProprietar())));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(l.getSuprafata())));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(l.getTipApartament())));

        row++;
    }

    QLayoutItem* item;
    while ((item = layoutBtnsTip->takeAt(0)) != nullptr) {
        delete item->widget(); // sterge widget
        delete item;           // sterge element de layout
    }

    // map pt numarare fiecare tip
    std::map<std::string, int> frecventeTipuri;
    for (const auto& l : srv.getAllLocatari()) {
        frecventeTipuri[l.getTipApartament()]++;
    }

    // parcurgem map si generam un buton pt fiecare tip gasit
    for (const auto& pereche : frecventeTipuri) {
        // first tip second nr
        QPushButton* btnTip = new QPushButton(QString::fromStdString(pereche.first));
        layoutBtnsTip->addWidget(btnTip);

        // conectam
        std::string tipCurent = pereche.first;
        int numarAparitii = pereche.second;

        QObject::connect(btnTip, &QPushButton::clicked, [this, tipCurent, numarAparitii]() {
            QMessageBox::information(this, "Informații Tip",
                QString("Avem %1 apartamente de tipul: %2")
                .arg(numarAparitii)
                .arg(QString::fromStdString(tipCurent)));
            });
    }
}


// fereastra de notificari

NotificareGUI::NotificareGUI(LocatarService& srv) : srv{ srv } {
    initGUI();
    connectSignals();
    setWindowTitle("Lista de Notificari");
    resize(300, 400);
}

void NotificareGUI::initGUI() {
    QVBoxLayout* mainL = new QVBoxLayout;
    this->setLayout(mainL);

    lstNotificari = new QListWidget;
    mainL->addWidget(lstNotificari);

    QHBoxLayout* genL = new QHBoxLayout;
    editNumarGenereaza = new QLineEdit;
    editNumarGenereaza->setPlaceholderText("Nr. apartamente...");
    btnGenereaza = new QPushButton("Genereaza Aleator");
    genL->addWidget(editNumarGenereaza);
    genL->addWidget(btnGenereaza);

    btnGoleste = new QPushButton("Goleste Lista");

    mainL->addLayout(genL);
    mainL->addWidget(btnGoleste);


    // zona export      *
    QHBoxLayout* exportL = new QHBoxLayout;
    editNumeFisierExport = new QLineEdit;
    editNumeFisierExport->setPlaceholderText("Nume fisier export (ex: test.csv / test.html)");
    btnExport = new QPushButton("Exporta Lista");

    exportL->addWidget(editNumeFisierExport);
    exportL->addWidget(btnExport);
    mainL->addLayout(exportL);
}

void NotificareGUI::connectSignals() {
    QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
        int nr = editNumarGenereaza->text().toInt();
        srv.genereazaListaNotificare(nr);
        reloadList();
        });

    QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
        srv.golesteListaNotificare();
        reloadList();
        });

    // *connect export
    QObject::connect(btnExport, &QPushButton::clicked, [&]() {
        std::string fisier = editNumeFisierExport->text().toStdString();

        if (fisier.empty()) {
            QMessageBox::warning(this, "Eroare", "Introdu numele fisierului in care vrei sa exporti!");
            return;
        }

        try {
            srv.exportaListaNotificare(fisier);
            QMessageBox::information(this, "Succes", "Export!");
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Eroare Export", QString::fromStdString(ex.getMesaj()));
        }
        });
}

void NotificareGUI::reloadList() {
    lstNotificari->clear();
    for (const auto& l : srv.getListaNotificare()) {
        QString itemText = QString("Ap: %1 | %2").arg(l.getApartament()).arg(QString::fromStdString(l.getNumeProprietar()));
        lstNotificari->addItem(itemText);
    }
}

void NotificareGUI::actualizeaza() {
    reloadList();
}