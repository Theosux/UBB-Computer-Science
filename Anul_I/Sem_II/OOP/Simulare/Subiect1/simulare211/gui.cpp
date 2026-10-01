#include "gui.h"
#include <QString>

MagazinGUI::MagazinGUI(ServiceRochii& srv) : srv{ srv } {
	initGUI();
	connectSignals();
	reloadList(srv.getAll());
}

void MagazinGUI::initGUI() {
	//layout principal(HORIZONTAL): lista in stanga butoane in dreapta
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	//in stanga un nou layout
	QVBoxLayout* layoutStanga = new QVBoxLayout;

	//in stanga punem lista
	lst = new QListWidget;
	layoutStanga->addWidget(lst);

	//tabelul
	table = new QTableWidget(0, 3);
	QStringList headerLabels;
	headerLabels << "Denumire" << "Marime" << "Pret";
	table->setHorizontalHeaderLabels(headerLabels);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//design
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);					//edit
	layoutStanga->addWidget(table);

	// add la main
	mainLayout->addLayout(layoutStanga);

	//in dreapta punem un layout VERTICAL pt butoane
	QVBoxLayout* dreaptaLayout = new QVBoxLayout;

	//zona adaugare in partea dreapta
	QFormLayout* formLayout = new QFormLayout;
	editCod = new QLineEdit;
	editDenumire = new QLineEdit;
	editMarime = new QLineEdit;
	editPret = new QLineEdit;

	formLayout->addRow("Cod:", editCod);
	formLayout->addRow("Denumire:", editDenumire);
	formLayout->addRow("Marime (S/M/L/XL):", editMarime);
	formLayout->addRow("Pret:", editPret);

	dreaptaLayout->addLayout(formLayout);
	//... final zona adaugare

	btnAdauga = new QPushButton("Adauga Rochie"); // buton adaugare
	btnSterge = new QPushButton("Sterge Rochie"); // buton stergere
	btnInchiriaza = new QPushButton("Inchiriaza Rochie");
	btnSortMarime = new QPushButton("Sortare Marime");
	btnSortPret = new QPushButton("Sortare Pret");
	btnNesortat = new QPushButton("Nesortat");

	dreaptaLayout->addWidget(btnAdauga);
	dreaptaLayout->addWidget(btnSterge);
	dreaptaLayout->addWidget(btnInchiriaza);
	dreaptaLayout->addWidget(btnSortMarime);
	dreaptaLayout->addWidget(btnSortPret);
	dreaptaLayout->addWidget(btnNesortat);
	dreaptaLayout->addStretch(); // impinge butoanele

	mainLayout->addLayout(dreaptaLayout);
}

void MagazinGUI::reloadList(const std::vector<Rochie>& rochii) {
	lst->clear();

	// parte tabel inceput
	table->clearContents();
	table->setRowCount(int(rochii.size()));

	int row = 0;


	for (const auto& r : rochii) {
		// construim designul cerut
		QString text = QString::fromStdString(r.getDenumire()) + " | Marime: " + QString::fromStdString(r.getMarime()) + " | Pret: " + QString::number(r.getPret()) + " RON";
		QListWidgetItem* item = new QListWidgetItem(text);

		//ascundem codul inauntru itemului
		item->setData(Qt::UserRole, r.getCod());
		item->setData(Qt::UserRole+1, r.isDisponibila());

		//colorare
		if (r.isDisponibila()) {
			item->setBackground(Qt::green);
		}
		else {
			item->setBackground(Qt::red);
		}
		lst->addItem(item);

		//PARTEA TABEL
		// Cream elementele pentru fiecare coloana in parte
		QTableWidgetItem* itemDenumire = new QTableWidgetItem(QString::fromStdString(r.getDenumire()));
		QTableWidgetItem* itemMarime = new QTableWidgetItem(QString::fromStdString(r.getMarime()));
		QTableWidgetItem* itemPret = new QTableWidgetItem(QString::number(r.getPret()));

		// Ascundem codul si in tabel (pe prima coloana e suficient)
		itemDenumire->setData(Qt::UserRole, r.getCod());
		itemDenumire->setData(Qt::UserRole+1, r.isDisponibila());

		// Coloram toate cele 3 celule ale randului
		if (r.isDisponibila()) {
			itemDenumire->setBackground(Qt::green);
			itemMarime->setBackground(Qt::green);
			itemPret->setBackground(Qt::green);
		}
		else {
			itemDenumire->setBackground(Qt::red);
			itemMarime->setBackground(Qt::red);
			itemPret->setBackground(Qt::red);
		}

		//populare tabel
		table->setItem(row, 0, itemDenumire);
		table->setItem(row, 1, itemMarime);
		table->setItem(row, 2, itemPret);

		row++;
	}
}

void MagazinGUI::connectSignals() {
	// 1. Cand dam click in LISTA, selectam automat acelasi rand si in TABEL
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		int selRow = lst->currentRow(); // aflam ce rand am selectat
		if (selRow >= 0) {
			table->selectRow(selRow);   // selectam acelasi rand in tabel
		}
	});

	// 2. Cand dam click in TABEL, selectam automat acelasi rand si in LISTA
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
		int selRow = table->currentRow(); // aflam ce rand am selectat
		if (selRow >= 0) {
			lst->setCurrentRow(selRow);   // selectam acelasi rand in lista
		}
	});

	// pop up disponibilitate
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		if (lst->selectedItems().empty()) {
			return;
		}
		QListWidgetItem* item = lst->selectedItems().at(0);
		if (item->data(Qt::UserRole + 1) == false) {
			QMessageBox::information(this, "Info", "Nu e disponibil");
		}
	});


	//adaugare
	QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
		QString codStr = editCod->text();
		std::string denumire = editDenumire->text().toStdString();
		std::string marime = editMarime->text().toStdString();
		QString pretStr = editPret->text();	

		int cod = codStr.toInt();
		double pret = pretStr.toDouble();

		try {
			// Incercam adaugarea prin Service
			srv.adaugaRochie(cod, denumire, marime, pret);

			// Daca a reusit, actualizam lista vizuala si golim casutele
			reloadList(srv.getAll());

			editCod->clear();
			editDenumire->clear();
			editMarime->clear();
			editPret->clear();

			QMessageBox::information(this, "Succes", "Rochia a fost adaugata cu succes!");
		}
		catch (const ValidException& ex) {
			QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(ex.getMesaj()));
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Eroare Repository", QString::fromStdString(ex.getMesaj()));
		}
		});
	// stergere
	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
		// verificam daca e selectat ceva
		if (lst->selectedItems().isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selecteaza o rochie din lista pt stergere!");
			return;
		}
		// extragem elementul
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		int cod = selItem->data(Qt::UserRole).toInt();
		try {
			srv.stergeRochie(cod);
			reloadList(srv.getAll());
			QMessageBox::information(this, "Succes", "Rochia a fost stearsa!");
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
		}
		});
	// inchiriere
	QObject::connect(btnInchiriaza, &QPushButton::clicked, [&]() {
		if (lst->selectedItems().isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selecteaza o rochie din lista!");
			return;
		}
		//Extragem el selectat
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		//extragere cod ascuns
		int cod = selItem->data(Qt::UserRole).toInt();

		try {
			srv.inchiriazaRochie(cod);
			reloadList(srv.getAll());
			QMessageBox::information(this, "Succes", "Rochie Inchiriata!");
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Indisponibil", QString::fromStdString(ex.getMesaj()));
		}
		});
	// sortare
	QObject::connect(btnSortMarime, &QPushButton::clicked, [&]() {
		reloadList(srv.sorteazaDupaMarime());
		});
	QObject::connect(btnSortPret, &QPushButton::clicked, [&]() {
		reloadList(srv.sorteazaDupaPret());
		});
	QObject::connect(btnNesortat, &QPushButton::clicked, [&]() {
		reloadList(srv.getAll());
		});
}