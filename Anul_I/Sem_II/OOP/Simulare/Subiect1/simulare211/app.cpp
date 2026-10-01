#include <QApplication>
#include "gui.h"
#include "teste.h"

int main(int argc, char* argv[]) {
	testAll();
	QApplication a(argc, argv);

	RepoRochii repo{ "rochie.txt" };
	ServiceRochii srv{ repo };

	MagazinGUI gui{ srv };
	gui.setWindowTitle("Magazin Inchirieri Rochii");
	gui.resize(1000, 500);
	gui.show();

	return a.exec();
}