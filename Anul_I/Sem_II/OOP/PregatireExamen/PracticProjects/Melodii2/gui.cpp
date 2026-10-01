#include "gui.h"

/*
stânga-sus → pop
dreapta-sus → rock
stânga-jos → folk
dreapta-jos → disco
*/

MelodiiGUI::MelodiiGUI(ServiceMelodii& srv) : srv{ srv } {
	initGUI();
	connectSignals();
	reloadAll();
}

void MelodiiGUI::initGUI() {
	//layout principal vertical: tabel sus, form jos
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	//cerinta 5: lasam spatiu in colturi pt cercuri
	mainLayout->setContentsMargins(100, 100, 100, 100);

	//tabelul cu model custom
	model = new MelodiiTableModel;
	tableView = new QTableView;
	tableView->setModel(model);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mainLayout->addWidget(tableView);

	//zona adaugare
	QFormLayout* formLayout = new QFormLayout;
	adTitlu = new QLineEdit;
	adArtist = new QLineEdit;
	adGen = new QLineEdit;
	formLayout->addRow("Titlu:", adTitlu);
	formLayout->addRow("Artist:", adArtist);
	formLayout->addRow("Gen:", adGen);
	mainLayout->addLayout(formLayout);

	//butoane
	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnAdauga = new QPushButton("Adauga");
	btnDelete = new QPushButton("Sterge");
	btnLayout->addWidget(btnAdauga);
	btnLayout->addWidget(btnDelete);
	mainLayout->addLayout(btnLayout);
}

void MelodiiGUI::connectSignals() {
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
			srv.stergereMelodie(id);
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
	//adaugare
	QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
		std::string titlu = adTitlu->text().toStdString();
		std::string artist = adArtist->text().toStdString();
		std::string gen = adGen->text().toStdString();

		try {
			// Incercam adaugarea prin Service
			srv.adaugaMelodie(titlu, artist, gen);

			// Daca a reusit, actualizam si golim casutele
			reloadAll();

			adTitlu->clear();
			adArtist->clear();
			adGen->clear();

			QMessageBox::information(this, "Succes", "Melodia a fost adaugata cu succes!");
		}
		catch (const ValidException& ex) {
			QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(ex.getMesaj()));
		}
		catch (const RepoException& ex) {
			QMessageBox::warning(this, "Eroare Repository", QString::fromStdString(ex.getMesaj()));
		}
		});
}

void MelodiiGUI::reloadAll() {
	//refacerea tabelului
	model->setMelodii(srv.getAllSortateArtist());
	update();	// cerinta 5: reface desenul la orice modificare
}

void MelodiiGUI::paintEvent(QPaintEvent* ev) {
	QWidget::paintEvent(ev);

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	int w = width();
	int h = height();

	//numaram melodiile din fiecare gen
	int nrPop = srv.numarMelodiiGen("pop");
	int nrRock = srv.numarMelodiiGen("rock");
	int nrFolk = srv.numarMelodiiGen("folk");
	int nrDisco = srv.numarMelodiiGen("disco");

	//cate un gen in fiecare colt
	deseneazaCercuri(p, QPoint(0, 0), nrPop, Qt::red);        //stanga-sus  = pop
	deseneazaCercuri(p, QPoint(w, 0), nrRock, Qt::blue);       //dreapta-sus = rock
	deseneazaCercuri(p, QPoint(0, h), nrFolk, Qt::darkGreen);  //stanga-jos  = folk
	deseneazaCercuri(p, QPoint(w, h), nrDisco, Qt::magenta);    //dreapta-jos = disco
}

void MelodiiGUI::deseneazaCercuri(QPainter& p, QPoint centru, int nrMelodii, QColor culoare) {
	p.setPen(QPen(culoare, 2));

	int razaMica = 12;	//cercul mic din colt
	int pas = 14;		//cu cat creste raza pentru fiecare melodie

	//cercul mic din colt
	p.drawEllipse(centru, razaMica, razaMica);

	//cate un cerc concentric pentru fiecare melodie din gen
	for (int i = 1; i <= nrMelodii; i++) {
		int raza = razaMica + i * pas;
		p.drawEllipse(centru, raza, raza);
	}
}