#include "RVOTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RVOTest w;
	w.show();
	return a.exec();
}
