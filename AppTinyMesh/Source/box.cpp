// Box

// Self include
#include "box.h"

/*!
\class Box box.h
\brief An axis aligned box.

The class stores the opposite two corners as vectors.
The center and the radius (diagonal vector) are computed on the
fly by inline functions.

The vertices of a box can be obtained by the Box::Vertex()
member function which returns one of the eight vertices of the box.
The two opposite corners can be obtained faster as follows:

\code
Box box(Vector(0.0,0.0,0.0),Vector(1.0,1.0,1.0)); // Unit box
Vector a=box[0]; // Lower vertex
Vector b=box[1]; // Opposite vertex
\endcode
*/

const double Box::epsilon = 1.0e-5; //!< Epsilon value used to check intersections and some round off errors.
const Box Box::Null(0.0); //!< Null box, equivalent to: \code Box(Vector(0.0)); \endcode 

const int Box::edge[24] =
{
  0,1,2,3,4,5,6,7,
  0,2,1,3,4,6,5,7,
  0,4,1,5,2,6,3,7
};

const Vector Box::normal[6] =
{
  Vector(-1.0,0.0,0.0),
  Vector(0.0,-1.0,0.0),
  Vector(0.0,0.0,-1.0),
  Vector(1.0,0.0,0.0),
  Vector(0.0, 1.0,0.0),
  Vector(0.0,0.0,1.0)
};

/*!
\brief Create a box given a center point and the half side length.
\param c Center.
\param r Half side length.
*/
Box::Box(const Vector& c, double r)
{
  a = c - Vector(r);
  b = c + Vector(r);
}

/*!
\brief Create a box given two opposite corners.

Note that this constructor does not check the coordinates of the two vectors.
Therefore, the coordinates of a should be lower than those of b.

To create the axis aligned bounding box of two vectors a and b in
the general case, one should use:
\code
Box box(Vector::Min(a,b),Vector::Max(a,b));
\endcode
\param a,b End vertices.
*/
Box::Box(const Vector& a, const Vector& b)
{
  Box::a = a;
  Box::b = b;
}

/*!
\brief Create a cube centered at the origin and of given half side length.

This is equivalent to:
\code
Box box(Vector(0.0),2.0);  // Simplified constructor Box(2.0);
\endcode
\param r Half side length.
*/
Box::Box(double r)
{
  a = -Vector(r);
  b = Vector(r);
}

/*!
\brief Creates the bounding box of a set of points.
\param v Array of vertices.
*/
Box::Box(const std::vector<Vector>& v)
{
  for (int j = 0; j < 3; j++)
  {
    a[j] = v.at(0)[j];
    b[j] = v.at(0)[j];
    for (int i = 1; i < v.size(); i++)
    {
      if (v.at(i)[j] < a[j])
      {
        a[j] = v.at(i)[j];
      }
      if (v.at(i)[j] > b[j])
      {
        b[j] = v.at(i)[j];
      }
    }
  }
}

/*!
\brief Create a box embedding two boxes.
\param x,y Argument boxes.
*/
Box::Box(const Box& x, const Box& y)
{
  a = Vector::Min(x.a, y.a);
  b = Vector::Max(x.b, y.b);
}

/*!
\brief Computes the sub-box in the n-th octant.
\param n Octant index.
*/
Box Box::Sub(int n) const
{
  Vector c = Center();
  return Box(Vector((n & 1) ? c[0] : a[0], (n & 2) ? c[1] : a[1], (n & 4) ? c[2] : a[2]),
    Vector((n & 1) ? b[0] : c[0], (n & 2) ? b[1] : c[1], (n & 4) ? b[2] : c[2]));
}

/*!
\brief Overloaded.
\param s Stream.
\param box The box.
*/
std::ostream& operator<<(std::ostream& s, const Box& box)
{
  s << "Box(" << box.a << ',' << box.b << ")";
  return s;
}

/*!
\brief Translates a box.

\param t Translation vector.
*/
void Box::Translate(const Vector& t)
{
  a += t;
  b += t;
}

/*!
\brief Scales a box.

Note that this function handles negative coefficients in
the scaling vector (by swapping coordinates if need be).
\param s Scaling.
*/
void Box::Scale(double s)
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
