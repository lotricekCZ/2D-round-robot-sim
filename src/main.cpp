/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include "user_interface/interface.hpp"

int main(int argc, char ** argv) {
	
	QApplication app(argc, argv);

	interface window;
    window.show();

	return app.exec();
}
