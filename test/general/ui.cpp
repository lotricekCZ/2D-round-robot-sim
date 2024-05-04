/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
	
	QApplication app(argc, argv);

	QWidget window;

	window.setWindowTitle("Editor");
	window.show();

	return app.exec();
}
