#include "gui.h"

MelodiiGUI::MelodiiGUI(ServiceMelodii& srv) : srv{ srv } {
	initGUI();
	connectSignals();
	reloadAll();
}

void MelodiiGUI::initGUI() {
	//layout principal vertical: tabel sus, formular la mijloc, grafic jos
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	//tabelul cu model custom
	model = new MelodiiTableModel;
	tableView = new QTableView;
	tableView->setModel(model);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mainLayout->addWidget(tableView);

	//zona modificare(titlu+rank)
	QFormLayout* formLayout = new QFormLayout;
	editTitlu = new QLineEdit;

	sliderRank = new QSlider(Qt::Horizontal);
	sliderRank->setMinimum(0);
	sliderRank->setMaximum(10);

	lblRank = new QLabel("0");

	//slider si eticheta pe acelasi rand
	QHBoxLayout* rankLayout = new QHBoxLayout;
	rankLayout->addWidget(sliderRank);
	rankLayout->addWidget(lblRank);

	formLayout->addRow("Titlu:", editTitlu);
	formLayout->addRow("Rank:", rankLayout);
	mainLayout->addLayout(formLayout);

	//butoanele
	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnUpdate = new QPushButton("Update");
	btnDelete = new QPushButton("Delete");
	btnLayout->addWidget(btnUpdate);
	btnLayout->addWidget(btnDelete);
	mainLayout->addLayout(btnLayout);

	//graficul cu bare jos
	grafic = new GraficMelodii;
	mainLayout->addWidget(grafic);
}

void MelodiiGUI::connectSignals() {
	//cand misc slider-ul, actualizez eticheta cu valoarea
	QObject::connect(sliderRank, &QSlider::valueChanged, [&](int val) {
		lblRank->setText(QString::number(val));
		});

	//cand selectez un rand in tabel, incarc titlul si rank-ul melodiei
	QObject::connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		QModelIndexList selectie = tableView->selectionModel()->selectedRows();
		if (selectie.isEmpty()) {
			return;
		}
		int row = selectie.at(0).row();
		Melodie m = model->getMelodieAt(row);
		editTitlu->setText(QString::fromStdString(m.getTitlu()));
		sliderRank->setValue(m.getRank());
		});

	//update
	QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
		QModelIndexList selectie = tableView->selectionModel()->selectedRows();
		if (selectie.isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selecteaza o melodie din tabel!");
			return;
		}
		int row = selectie.at(0).row();
		int id = model->getMelodieAt(row).getId();

		std::string titluNou = editTitlu->text().toStdString();
		int rankNou = sliderRank->value();

		try {
			srv.modificaMelodie(id, titluNou, rankNou);
			reloadAll();
			QMessageBox::information(this, "Succes", "Melodia a fost modificata!");
		}
		catch (const ValidException& ex) {
			QMessageBox::warning(this, "Eroare validare", QString::fromStdString(ex.getMesaj()));
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
		}
		});

	//delete
	QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
		QModelIndexList selectie = tableView->selectionModel()->selectedRows();
		if (selectie.isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selecteaza o melodie din tabel!");
			return;
		}
		int row = selectie.at(0).row();
		int id = model->getMelodieAt(row).getId();

		try {
			srv.stergeMelodie(id);
			reloadAll();
			QMessageBox::information(this, "Succes", "Melodia a fost stearsa!");
		}
		catch (const ValidException& ex) {
			//cazul "ultima melodie a artistului"
			QMessageBox::warning(this, "Info", QString::fromStdString(ex.getMesaj()));
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMesaj()));
		}
		});
}

void MelodiiGUI::reloadAll() {
	//tabelul: melodii sortate dupa rank
	model->setMelodii(srv.getAllSortateRank());
	//graficul: toate melodiile (numara singur pe rank-uri)
	grafic->setMelodii(srv.getAll());
}