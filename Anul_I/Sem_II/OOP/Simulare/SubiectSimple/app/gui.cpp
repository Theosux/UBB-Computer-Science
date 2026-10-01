/*
Masini: id, specie, nume, varsta.
Am avut de implementat un QTable care avea lista populata din fisier la inceput cu toate in afara de id.
fiecare rand trebuia colorat in functie de ce "specie" era: ex: SUV => rand grey...
Daca varsta masinii > 10  atunci cand se selecteaza randu sa apara un pop-up cu "Animalul este prea in varsta!".
Sa aiba 3 butoane: sortare dupa an,
filtrare dupa specie si reset.
*/

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
	this->setLayout(mainLayout);

	//stanga
	QVBoxLayout* layoutStanga = new QVBoxLayout;

	table = new QTableWidget(0, 3);
	QStringList headerLabels;
	headerLabels << "Marca" << "Model" << "An";
	table->setHorizontalHeaderLabels(headerLabels);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//design
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);					//edit
	layoutStanga->addWidget(table);

	mainLayout->addLayout(layoutStanga);

	QVBoxLayout* layoutDreapta = new QVBoxLayout;

	QFormLayout* formLayout = new QFormLayout;
	editMarca = new QLineEdit;
	formLayout->addRow("Marca:", editMarca);

	btnSortare = new QPushButton("Sorteaza dupa an");
	btnFiltrare = new QPushButton("Filtreaza dupa marca");
	btnReset = new QPushButton("Reset");

	layoutDreapta->addLayout(formLayout);

	layoutDreapta->addWidget(btnSortare);
	layoutDreapta->addWidget(btnFiltrare);
	layoutDreapta->addWidget(btnReset);

	mainLayout->addLayout(layoutDreapta);
}

void MasiniGUI::reloadTable(const std::vector<Masina>& masini) {
	table->clearContents();
	table->setRowCount(int(masini.size()));
	int row = 0;
	for (const auto& m : masini) {
		QString text = QString::fromStdString(m.getMarca()) + " | Model: " + QString::fromStdString(m.getModel()) + " | An: " + QString::number(m.getAn());
		
		QTableWidgetItem* itemId = new QTableWidgetItem(QString::number(m.getId()));
		QTableWidgetItem* itemMarca = new QTableWidgetItem(QString::fromStdString(m.getMarca()));
		QTableWidgetItem* itemModel = new QTableWidgetItem(QString::fromStdString(m.getModel()));
		QTableWidgetItem* itemAn = new QTableWidgetItem(QString::number(m.getAn()));

		//asociem id model si an
		itemMarca->setData(Qt::UserRole, m.getId());
		itemMarca->setData(Qt::UserRole + 1, QString::fromStdString(m.getModel()));
		itemMarca->setData(Qt::UserRole + 2, m.getAn());

		//colorare
		if (m.getModel() == "SUV") {
			itemId->setBackground(Qt::gray);
			itemMarca->setBackground(Qt::gray);
			itemModel->setBackground(Qt::gray);
			itemAn->setBackground(Qt::gray);
		}
		if (m.getModel() == "Sedan") {
			itemId->setBackground(Qt::green);
			itemMarca->setBackground(Qt::green);
			itemModel->setBackground(Qt::green);
			itemAn->setBackground(Qt::green);
		}
		// populare
		table->setItem(row, 0, itemMarca);
		table->setItem(row, 1, itemModel);
		table->setItem(row, 2, itemAn);

		row++;
	}
}

void MasiniGUI::connectSignals() {
	// pop up varsta
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
		if (table->selectedItems().empty()) {
			return;
		}
		QTableWidgetItem* item = table->selectedItems().at(0);
		if (item->data(Qt::UserRole + 2).toInt() > 10) {
			QMessageBox::information(this, "Info", "Masina are mai mult de 10 ani!");
		}
	});
	QObject::connect(btnSortare, &QPushButton::clicked, [&]() {
		reloadTable(srv.sortareAn());
	});
	QObject::connect(btnFiltrare, &QPushButton::clicked, [&]() {
		std::string marcaCautata = editMarca->text().toStdString();

		if (marcaCautata.empty()) {
			QMessageBox::warning(this, "Eroare", "Scrie o marca!");
			return;
		}
		reloadTable(srv.filtrareMarca(marcaCautata));
	});
	QObject::connect(btnReset, &QPushButton::clicked, [&]() {
		reloadTable(srv.getAll());
	});
}