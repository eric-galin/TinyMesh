#include "qte.h"

int main(int argc, char *argv[])
{
    //Mesh m(Cylinder(Vector(-1.0, 0.0, 0.0), Vector(1.0, 1.0, 0.0), 1), 64);
    Mesh m(Sphere(Vector(0., 0., 0.), 10), 4);
    //Mesh m(Box(Vector(0., 0., 0.), 4.));

    m.SaveObj(QString("cube.obj"), QString("cube"));

    m.TriangleSubdivision(2);

    m.SaveObj(QString("cube_sub.obj"), QString("cube"));

	return 0;
}
