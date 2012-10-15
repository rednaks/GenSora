#include "authWindow.h"
#include <QApplication>

int main(int argc, char **argv) {

	QApplication app(argc, argv);

	AuthWindow win;
	win.show();
	
	return app.exec();

}
