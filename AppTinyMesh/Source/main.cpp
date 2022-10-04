#include "qte.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWin;
	mainWin.showMaximized();
	//Mesh testObject = Mesh(Cylinder(Vector(-1.0, 0.0, 0.0), Vector(1.0, 0.0, 0.0), 1), 64);
	//testObject.SaveObj("testObject.obj","testObject");

	return app.exec();
}
