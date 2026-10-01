#include "grafic.h"
#include <QPainter>

GraficMelodii::GraficMelodii(QWidget* parent) : QWidget{ parent } {
	setMinimumHeight(150);	// rezervam loc pt desen
}

void GraficMelodii::setMelodii(const std::vector<Melodie>& melodiiNoi) {
	melodii = melodiiNoi;
	update();				// cere redesenarea (apeleaza paintEvent)
}

void GraficMelodii::paintEvent(QPaintEvent*) {
	QPainter painter(this);

	const int NR_BARE = 11;		// rank-urile posibile: 0,1,...,10

	//numaram cate melodii sunt pe fiecare rank
	std::vector<int> counts(NR_BARE, 0);
	for (const auto& m : melodii) {
		int r = m.getRank();
		if (r >= 0 && r < NR_BARE) {
			counts[r]++;
		}
	}

	//aflam maximul ca sa scalam inaltimea barelor
	int maxCount = 1;			// minim 1 ca sa nu impartim la 0
	for (int c : counts) {
		if (c > maxCount) maxCount = c;
	}

	int W = width();
	int H = height();
	int spatiuText = 20;		// loc rezervat jos pt etichete
	int inaltimeUtila = H - spatiuText;
	int latimeBara = W / NR_BARE;

	for (int i = 0; i < NR_BARE; i++) {
		//inaltimea proportionala cu numarul de melodii de rank i
		int inaltimeBara = (counts[i] * inaltimeUtila) / maxCount;

		int x = i * latimeBara;
		int y = inaltimeUtila - inaltimeBara;

		//desenam bara
		painter.setBrush(Qt::blue);
		painter.drawRect(x + 2, y, latimeBara - 4, inaltimeBara);

		//sub bara scriem rank-ul
		painter.drawText(x + 2, H - 5, QString::number(i));
	}
}