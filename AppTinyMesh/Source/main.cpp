#include "qte.h"

int main(int argc, char *argv[])
{
    //Mesh m(Cylinder(Vector(-1.0, 0.0, 0.0), Vector(1.0, 1.0, 0.0), 1), 64);
    Mesh m(Sphere(Vector(0., 0., 0.), 1), 20);
    //Mesh m(Box(Vector(0., 0., 0.), 4.));

    m.SaveObj(QString("objet.obj"), QString("cube"));


	return 0;
}
