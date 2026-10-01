#include <QApplication>
#include "gui.h"
#include "tests.h"

int main(int argc, char* argv[]) {
	testAll();
	QApplication a(argc, argv);

	RepoMasini repo{ "masina.txt" };
	ServiceMasini srv{ repo };

	MasiniGUI gui{ srv };
	gui.setWindowTitle("Gestionare Masini");
	gui.resize(1000, 500);
	gui.show();

	return a.exec();
}