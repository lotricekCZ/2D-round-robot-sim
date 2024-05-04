#include <QApplication>
#include <QMainWindow>
#include "../../src/user_interface/interface.hpp"

int main(int argc, char ** argv) {
	
	QApplication app(argc, argv);

	interface window;
    window.show();

	return app.exec();
}
