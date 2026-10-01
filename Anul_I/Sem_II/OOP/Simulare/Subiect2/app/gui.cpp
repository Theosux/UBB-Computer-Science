#include "gui.h"
#include <QString>

ParcAutoGUI::ParcAutoGUI(ServiceMasini& srv) : srv{ srv } {
	initGUI();
	connectSignals();
	reloadList(srv.getAll());
}

void ParcAutoGUI::initGUI() {
	//layout principal (horizontal) : lista in stanga butoane in dreapta
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	//in stanga un layout
	QVBoxLayout* layoutStanga = new QVBoxLayout;

	//in stanga punem lista
	lst = new QListWidget;
	layoutStanga->addWidget(lst);

	//tabelul
	table = new QTableWidget(0, 4);
	QStringList headerLabels;
	headerLabels << "ID" << "Marca" << "Model" << "Pret";
	table->setHorizontalHeaderLabels(headerLabels);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//design
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);					//edit
	layoutStanga->addWidget(table);

	//add la main
	mainLayout->addLayout(layoutStanga);

	//in dreapta vertical pt butoane
	QVBoxLayout* dreaptaLayout = new QVBoxLayout;

	//zona adaugare in partea dreapta
	QFormLayout* formLayout = new QFormLayout;
	editId = new QLineEdit;
	editMarca = new QLineEdit;
	editModel = new QLineEdit;
	editPretZi = new QLineEdit;

	formLayout->addRow("Id:", editId);
	formLayout->addRow("Marca:", editMarca);
	formLayout->addRow("Model:", editModel);
	formLayout->addRow("Pret:", editPretZi);

	dreaptaLayout->addLayout(formLayout);

	btnAdauga = new QPushButton("Adauga Masina");
	btnSterge = new QPushButton("Sterge Masina");
	btnInchiriaza = new QPushButton("Inchiriaza Masina");
	btnSortMarca = new QPushButton("Sorteaza Marca");
	btnSortPret = new QPushButton("Sorteaza Pret");
	btnFiltrareMarca = new QPushButton("Filtreaza Marca");
	btnNesortat = new QPushButton("Reset");

	dreaptaLayout->addWidget(btnAdauga);
	dreaptaLayout->addWidget(btnSterge);
	dreaptaLayout->addWidget(btnInchiriaza);
	dreaptaLayout->addWidget(btnSortMarca);
	dreaptaLayout->addWidget(btnSortPret);
	dreaptaLayout->addWidget(btnFiltrareMarca);
	dreaptaLayout->addWidget(btnNesortat);

	mainLayout->addLayout(dreaptaLayout);
}

void ParcAutoGUI::reloadList(const std::vector<Masina>& masini) {
	lst->clear();

	// inceput tabel
	table->clearContents();
	table->setRowCount(int(masini.size()));

	int row = 0;

	for (const auto& m : masini) {
		QString text = QString::number(m.getId()) + " | Marca: " + QString::fromStdString(m.getMarca()) + " | Model: " + QString::fromStdString(m.getModel()) + " | Pret: " + QString::number(m.getPretZi()) + " EUR";
		QListWidgetItem* item = new QListWidgetItem(text);

		//asociem id cu itemul
		item->setData(Qt::UserRole, m.getId());
		item->setData(Qt::UserRole + 1, m.isDisponibila());

		//colorare
		if (m.isDisponibila()) {
			item->setBackground(Qt::green);
		}
		else {
			item->setBackground(Qt::red);
		}
		lst->addItem(item);

		//Parte Tabel
		QTableWidgetItem* itemId = new QTableWidgetItem(QString::number(m.getId()));
		QTableWidgetItem* itemModel = new QTableWidgetItem(QString::fromStdString(m.getModel()));
		QTableWidgetItem* itemMarca = new QTableWidgetItem(QString::fromStdString(m.getMarca()));
		QTableWidgetItem* itemPret = new QTableWidgetItem(QString::number(m.getPretZi()));

		//ascundem id si disponibilitatea
		itemId->setData(Qt::UserRole, m.getId());
		itemId->setData(Qt::UserRole+1, m.isDisponibila());

		//colorare toate cele 4 elemente
		if (m.isDisponibila()) {
			itemId->setBackground(Qt::green);
			itemModel->setBackground(Qt::green);
			itemMarca->setBackground(Qt::green);
			itemPret->setBackground(Qt::green);
		}
		else {
			itemId->setBackground(Qt::red);
			itemModel->setBackground(Qt::red);
			itemMarca->setBackground(Qt::red);
			itemPret->setBackground(Qt::red);
		}

		//populare
		table->setItem(row, 0, itemId);
		table->setItem(row, 1, itemMarca);
		table->setItem(row, 2, itemModel);
		table->setItem(row, 3, itemPret);

		row++;
	}
}

void ParcAutoGUI::connectSignals() {
	// conectare lista-tabel
	// lista -> tabel
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		int selRow = lst->currentRow(); // aflam ce rand am selectat
		if (selRow >= 0) {
			table->selectRow(selRow);   // selectam acelasi rand in tabel
		}
	});


	// tabel -> lista
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
		if (item->data(Qt::UserRole + 1) == true) {
			QMessageBox::information(this, "Info", "Masina este disponibila!");
		}
	});

	// adaugare
	QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
		QString idStr = editId->text();
		std::string marca = editMarca->text().toStdString();
		std::string model = editModel->text().toStdString();
		QString pretStr = editPretZi->text();

		int id = idStr.toInt();
		double pret = pretStr.toDouble();

		try {
			// adaugare in service
			srv.adaugaMasina(id, marca, model, pret);

			// refresh lista si golim casutele
			reloadList(srv.getAll());
			editId->clear();
			editMarca->clear();
			editModel->clear();
			editPretZi->clear();

			QMessageBox::information(this, "Succes", "Masina adaugata cu succes!");
		}
		catch (const ValidException& ex) {
			QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(ex.getMesaj()));
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Eroare Repo", QString::fromStdString(ex.getMesaj()));
		}
		});

	// stergere
	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
		if (lst->selectedItems().isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selecteaza o masina din lista pentru stergere!");
			return;
		}

		// luam elementul si id-ul ascuns
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		int id = selItem->data(Qt::UserRole).toInt();

		try {
			srv.stergeMasina(id);
			reloadList(srv.getAll());
			QMessageBox::information(this, "Succes", "Masina a fost stearsa!");
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
		}
		});

	// inchiriere
	QObject::connect(btnInchiriaza, &QPushButton::clicked, [&]() {
		if (lst->selectedItems().isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selecteaza o masina din lista pentru inchiriere!");
			return;
		}

		// luam elementul si id-ul ascuns
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		int id = selItem->data(Qt::UserRole).toInt();

		try {
			srv.inchiriazaMasina(id);
			reloadList(srv.getAll());
			QMessageBox::information(this, "Succes", "Masina a fost inchiriata!");
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Indisponibil", QString::fromStdString(ex.getMesaj()));
		}
		});

	// sortare dupa marca
	QObject::connect(btnSortMarca, &QPushButton::clicked, [&]() {
		reloadList(srv.sortareMarca());
		});

	// sortare dupa pret
	QObject::connect(btnSortPret, &QPushButton::clicked, [&]() {
		reloadList(srv.sortarePret());
		});

	// filtrare (dupa casuta de marca)
	QObject::connect(btnFiltrareMarca, &QPushButton::clicked, [&]() {
		std::string marcaCautata = editMarca->text().toStdString();

		if (marcaCautata.empty()) {
			QMessageBox::warning(this, "Eroare", "Scrie o marca in casuta 'Marca' pentru a putea filtra!");
			return;
		}

		reloadList(srv.filtrareMarca(marcaCautata));
		});

	// reset
	QObject::connect(btnNesortat, &QPushButton::clicked, [&]() {
		reloadList(srv.getAll());
		});
}