#include <QApplication>
#include "gui.h"
#include "teste.h"

int main(int argc, char* argv[]) {
	testAll();

	QApplication a(argc, argv);

	RepoMelodii repo{ "melodii.txt" };
	ServiceMelodii srv{ repo };

	MelodiiGUI gui{ srv };
	gui.setWindowTitle("Gestiune Melodii");
	gui.resize(900, 700);
	gui.show();

	return a.exec();
}