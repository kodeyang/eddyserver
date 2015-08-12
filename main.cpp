#include <QtWidgets/QApplication>
#include <QTextCodec>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	MainWindow main_window;
	main_window.show();
	return a.exec();
}