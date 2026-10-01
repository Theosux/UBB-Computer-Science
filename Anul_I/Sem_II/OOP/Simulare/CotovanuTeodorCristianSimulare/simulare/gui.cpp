#include "gui.h"
#include <QString>

MasiniGUI::MasiniGUI(ServiceMasini& srv) : srv{ srv } {
	initGui();
	connectSignals();
	reloadTable(srv.getAll());
}

void MasiniGUI::initGui() {
	//layout principal
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);												// punem primul layout principal in widgetul declarat ca clasa

	//stanga (tabelul)
	QVBoxLayout* stangaLayout = new QVBoxLayout;

	table = new QTableWidget(0, 3);
	QStringList headerLabels;
	headerLabels << "Denumire" << "Tip" << "Necesitati apa (ml/zi)";
	table->setHorizontalHeaderLabels(headerLabels);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);					// se selecteaza toata linia

	//qof
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//strech pt vizual
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);					//blocam edit in tabel


	stangaLayout->addWidget(table);

	mainLayout->addLayout(stangaLayout);

	//dreapta
	QVBoxLayout* dreaptaLayout = new QVBoxLayout;
	QFormLayout* formLayout = new QFormLayout;
	formApa = new QLineEdit;
	formLayout->addRow("Cantitate de apa:", formApa);

	btnSortare = new QPushButton("Sorteaza dupa tip");
	btnFiltrare = new QPushButton("Filtreaza dupa necesar apa");
	btnReset = new QPushButton("Reset");

	dreaptaLayout->addLayout(formLayout);

	dreaptaLayout->addWidget(btnSortare);
	dreaptaLayout->addWidget(btnFiltrare);
	dreaptaLayout->addWidget(btnReset);

	mainLayout->addLayout(dreaptaLayout);
}

void MasiniGUI::reloadTable(const std::vector<Masina>& masini) {
	table->clearContents();											// golim
	table->setRowCount(masini.size());								// nr de linii e nr de masini
	int row = 0;
	for (const auto& m : masini) {
		QString text = QString::fromStdString(m.getDenumire()) + " | Tip:" + QString::fromStdString(m.getTip()) + " | Necesitati apa(ml/zi)" + QString::number(m.getNecesarApa());

		QTableWidgetItem* itemCod = new QTableWidgetItem(QString::number(m.getCod()));
		QTableWidgetItem* itemDenumire = new QTableWidgetItem(QString::fromStdString(m.getDenumire()));
		QTableWidgetItem* itemTip = new QTableWidgetItem(QString::fromStdString(m.getTip()));
		QTableWidgetItem* itemApa = new QTableWidgetItem(QString::number(m.getNecesarApa()));

		//asociem apa pt pop up
		itemDenumire->setData(Qt::UserRole, m.getNecesarApa());

		//colorare
		if (m.getTip() == "electrica") {
			itemDenumire->setBackground(Qt::magenta);
			itemTip->setBackground(Qt::magenta);
			itemApa->setBackground(Qt::magenta);
		}
		if (m.getTip() == "hibrida") {
			itemDenumire->setBackground(Qt::cyan);
			itemTip->setBackground(Qt::cyan);
			itemApa->setBackground(Qt::cyan);
		}
		if (m.getTip() == "sport") {
			itemDenumire->setBackground(Qt::red);
			itemTip->setBackground(Qt::red);
			itemApa->setBackground(Qt::red);
		}
		if (m.getTip() == "SUV") {
			itemDenumire->setBackground(Qt::darkGray);
			itemTip->setBackground(Qt::darkGray);
			itemApa->setBackground(Qt::darkGray);
		}

		//umplem tabelul
		table->setItem(row, 0, itemDenumire);
		table->setItem(row, 1, itemTip);
		table->setItem(row, 2, itemApa);

		row++;
	}
}

void MasiniGUI::connectSignals() {
	//pop up apa
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {			// cand se intamla o schimbare in intemele schimbate din tabel
		if (table->selectedItems().empty()) {										// daca nu exista selectate iesim
			return;
		}
		QTableWidgetItem* item = table->selectedItems().at(0);						// altfel, luam itemul selectat, primul (va fi mereu doar 1)
		if (item->data(Qt::UserRole).toInt() > 300) {								// accesam ceea ce am stocat, adica apa
			QMessageBox::information(this, "info", "Masina are nevoie de spalare zilnica!");
		}
	});
	QObject::connect(btnSortare, &QPushButton::clicked, [&]() {
		reloadTable(srv.sortareTip());
	});
	// int necesarApa = std::stoi(necesarApaStr);
	QObject::connect(btnFiltrare, &QPushButton::clicked, [&]() {
		std::string apaF = formApa->text().toStdString();							// preluat drept stdstring
		if (apaF.empty()) {
			QMessageBox::warning(this, "Eroare", "introdu apa necesara!");
			return;
		}
		int apaFF = std::stoi(apaF);												// conversie int
		reloadTable(srv.filtrareApa(apaFF));
	});

	QObject::connect(btnReset, &QPushButton::clicked, [&]() {
		reloadTable(srv.getAll());
	});
}