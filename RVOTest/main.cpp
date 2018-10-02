#include "RVOTest.h"

#include <QtWidgets/QApplication>

#include "RVOWorld.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RVOTest w;
	w.show();
	RVOWorld world(&w);
	return a.exec();
}
