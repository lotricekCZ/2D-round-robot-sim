#include <QApplication>
#include <QMainWindow>
#include "../../src/user_interface/interface.hpp"

int main(int argc, char *argv[]) {
	
	QApplication app(argc, argv);

    QMainWindow widget;
	ui::MainWindow window;
	window.setupUi(&widget);
    widget.show();

	return app.exec();
}
