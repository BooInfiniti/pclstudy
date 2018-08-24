/*
#include "pclvisualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pclvisualizer w;
	w.show();
	return a.exec();
}
*/
#include "pclvisualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PCLVisualizer w;
	w.show();
	return a.exec();
}