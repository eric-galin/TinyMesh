// Vector  

// Self include
#include "mathematics.h"

#include <iostream>

/*!
\class Vector mathematics.h
\brief Vectors in three dimensions.

Most binary operators have been overloaded as expected,
destructive operators, such as addition and subtraction
have been implemented and behave as one could expect.

<P><I>How do I compute the cross product of two vectors?</I>
<BR>Simply use the overloaded Vector::operator/, for instance
\code
Vector c=a/b; // Cross product
\endcode
computes the cross product of a and b.
<P><I>How can I get access to the x, y and z components of a vector?</I>
<BR>Use v[0], v[1] and v[2] to get access to the x, y and z components of a vector v respectively.
<P><I>How do I compute the normal of a triangle?</I>
<BR>Let a,b,c the vertices of the triangle, simply compute the cross product
\code
Vector n=(a-b)/(a-c);  // Cross product
\endcode
or use the member function of the Triangle class:
\code
Vector n=Triangle(a,b,c).Normal(); // Compute the normal
\endcode
<P><I>How can I sort the three elements in a vector?</I>
<BR>Use Vector::Sort() as follows:
\code
Vector s=Vector(2.0,3.0,-1.0).Sort(); // Sort components in ascending order
\endcode

<P><I>How do I perform bi-linear interpolation on vectors?</I>
<BR>Use Vector::Bilinear() with four vectors and bilinear coordinates.
Alternatively, some geometric classes implement bilinear interpolation,
such as Quadrangle::Vertex().
*/

const Vector Vector::Null = Vector(0.0, 0.0, 0.0);
const Vector Vector::X = Vector(1.0, 0.0, 0.0);
const Vector Vector::Y = Vector(0.0, 1.0, 0.0);
const Vector Vector::Z = Vector(0.0, 0.0, 1.0);

/*!
\brief Normalize a vector, computing the inverse of its norm and scaling
the components.

This function does not check if the vector is null,
which might resulting in errors.
*/
void Normalize(Vector& u)
{
  u *= 1.0 / Norm(u);
}

/*!
\brief Returns a vector orthogonal to the argument vector.

The returned orthogonal vector is not computed randomly.
First, we find the two coordinates of the argument vector with
maximum absolute value. The orthogonal vector is defined by
swapping those two coordinates and changing one sign, whereas
the third coordinate is set to 0.

The returned orthogonal vector lies in the plane orthogonal
to the first vector.
*/
Vector Vector::Orthogonal() const
{
  Vector a = Abs(*this);
  int i = 0;
  int j = 1;
  if (a[0] > a[1])
  {
    if (a[2] > a[1])
    {
      j = 2;
    }
  }
  else
  {
    i = 1;
    j = 2;
    if (a[0] > a[2])
    {
      j = 0;
    }
  }
  a = Vector::Null;
  a[i] = c[j];
  a[j] = -c[i];
  return a;
}

/*!
\brief Overloaded output-stream operator.
\param u Vector.
\param s Stream.
*/
std::ostream& operator<<(std::ostream& s, const Vector& u)
{
  s << "Vector(" << u.c[0] << ',' << u.c[1] << ',' << u.c[2] << ')';
  return s;
}

/*!
\brief Given a vector, creates two vectors xand y that form an orthogonal basis.

This algorithm pickes the minor axis in order to reduce numerical instability
\param x, y Returned vectors such that (x,y,n) form an orthonormal basis (provided n is normalized).
*/
void Vector::Orthonormal(Vector& x, Vector& y) const
{
  x = Normalized(Orthogonal());
  y = Normalized(*this / x);
}
