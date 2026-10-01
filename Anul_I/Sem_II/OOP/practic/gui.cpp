#include "gui.h"

StudentGUI::StudentGUI(ServiceStudent& srv) : srv{ srv } {
	initGUI();
	connectSignals();
	reloadAll();
}

void StudentGUI::initGUI() {
	//layout principal vertical: tabel sus, butoane jos
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	//tabelul custom
	model = new StudentTabelModel;
	tableView = new QTableView;
	tableView->setModel(model);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mainLayout->addWidget(tableView);

	//butoane
	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnSterge = new QPushButton("Sterge");
	btnImbatranire = new QPushButton("Imbatranire");
	btnIntinerire = new QPushButton("Intinerire");
	btnUndo = new QPushButton("Undo");
	btnRedo = new QPushButton("Redo");
	btnLayout->addWidget(btnSterge);
	btnLayout->addWidget(btnImbatranire);
	btnLayout->addWidget(btnIntinerire);
	btnLayout->addWidget(btnUndo);
	btnLayout->addWidget(btnRedo);
	mainLayout->addLayout(btnLayout);
}

void StudentGUI::connectSignals() {
	//stergere student/i selectat
	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
		QModelIndexList selectieStergere = tableView->selectionModel()->selectedRows();
		if (selectieStergere.isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selecteaza cel putin un student!");
			return;
		}

		//colectam nr matricol pt toti
		std::vector<int> toDelete;
		for (const QModelIndex& idx : selectieStergere) {
			toDelete.push_back(model->getStudentAt(idx.row()).getNrMatricol());
		}

		try {
			for (int nrMatricol : toDelete) {
				srv.stergereStudent(nrMatricol);
			}
			reloadAll();
			QMessageBox::information(this, "Succes", "Studentii selectati au fost stersi!");
		}
		catch (const RepoException& ex) {
			reloadAll();	//facem update inainte de eroare
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
		}
		});

	//imbatranire: +1
	QObject::connect(btnImbatranire, &QPushButton::clicked, [&]() {
		srv.imbatranire();
		reloadAll();
		QMessageBox::information(this, "Succes", "Imbatranire!");
		});

	//intinerire: -1
	QObject::connect(btnIntinerire, &QPushButton::clicked, [&]() {
		srv.intinerire();
		reloadAll();
		QMessageBox::information(this, "Succes", "Intinerire!");
		});

	//undo
	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			reloadAll();
		}
		catch (const ValidException& ex) {
			QMessageBox::warning(this, "Info", QString::fromStdString(ex.getMesaj()));	//cazul in care nu se mai poate da
		}
		});
	//redo
	QObject::connect(btnRedo, &QPushButton::clicked, [&]() {
		try {
			srv.redo();
			reloadAll();
		}
		catch (const ValidException& ex) {
			QMessageBox::warning(this, "Info", QString::fromStdString(ex.getMesaj()));	//cazul in care nu se mai poate da
		}
		});
}

void StudentGUI::reloadAll() {
	//refacere tabel sortat
	model->setStudenti(srv.getAllSortatiVarsta());
}