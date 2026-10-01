#include <QApplication>
#include "gui.h"
#include "teste.h"

int main(int argc, char* argv[]) {
	testAll();

	QApplication a(argc, argv);

	RepoStudent repo{ "studenti.txt" };
	ServiceStudent srv{ repo };

	StudentGUI gui{ srv };
	gui.setWindowTitle("Gestiune Studenti");
	gui.resize(900, 700);
	gui.show();

	return a.exec();
}