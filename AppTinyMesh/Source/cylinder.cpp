// Cylinder

// Self include
#include "cylinder.h"

/*!
\class Cylinder cylinder.h
\brief A cylinder.

The class stores the opposite two corners as vectors.
The vertices of a cylinder can be obtained by the Cylinder::Vertex()
*/

const double Cylinder::epsilon = 1.0e-5; //!< Epsilon value used to check intersections and some round off errors.


/*!
\brief Create a cylinder given two vectors and a radius.

Note that this constructor does not check the coordinates of the two vectors.
Therefore, the coordinates of a should be lower than those of b.

To create a cylinder off of two vectors a and b in
the general case, one should use:
\code
Cylinder cyl(Vector(0.0,0.0,0.0),Vector(1.0,1.0,1.0), 1);
\endcode
\param a,b End circles vertices.
\param r cylinder radius.
*/
Cylinder::Cylinder(const Vector& a, const Vector& b, const double r)
{
    Cylinder::a = a;
    Cylinder::b = b;
    Cylinder::r = r;
}

/*!
\brief Overloaded.
\param s Stream.
\param cyl The cylinder.
*/
std::ostream& operator<<(std::ostream& s, const Cylinder& cyl)
{
    s << "Cylinder(" << cyl.a << ',' << cyl.b << ")";
    return s;
}

/*!
\brief Translates a cylinder.

\param t Translation vector.
*/
void Cylinder::Translate(const Vector& t)
{
    a += t;
    b += t;
}

/*!
\brief Scales a cylinder.

Note that this function handles negative coefficients in
the scaling vector (by swapping coordinates if need be).
\param s Scaling.
*/
void Cylinder::Scale(double s)
{
    a *= s;
    b *= s;

    // Swap coordinates for negative coefficients 
    if (s < 0.0)
    {
        Vector t = a;
        a = b;
        b = t;
    }
}
