// Box

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Box
{
protected:
  Vector a,b; //!< Lower and upper vertex.
public:
  //! Empty.
  Box() {}
  explicit Box(double);
  explicit Box(const Vector&, const Vector&);
  explicit Box(const Vector&, double);
  explicit Box(const std::vector<Vector>&);
  explicit Box(const Box&, const Box&);

  //! Empty.
  ~Box() {}

  // Access vertexes
  Vector& operator[] (int);
  Vector operator[] (int) const;

  // Comparison
  friend int operator==(const Box&, const Box&);
  friend int operator!=(const Box&, const Box&);

  // Acces to vertices
  Vector Center() const;
  Vector Vertex(int) const;

  Vector Size() const;
  Vector Diagonal() const;
  double Radius() const;

  bool Inside(const Box&) const;
  bool Inside(const Vector&) const;

  double Volume() const;
  double Area() const;

  // Compute sub-box
  Box Sub(int) const;

  // Translation, scale
  void Translate(const Vector&);
  void Scale(double);

  friend std::ostream& operator<<(std::ostream&, const Box&);

public:
  static const double epsilon; //!< Internal \htmlonly\epsilon;\endhtmlonly for ray intersection tests.
  static const Box Null; //!< Empty box.
  static const int edge[24]; //!< Edge vertices.
  static const Vector normal[6]; //!< Face normals.
};

//! Returns either end vertex of the box.
inline Vector& Box::operator[] (int i)
{
  if (i == 0) return a;
  else return b;
}

//! Overloaded.
inline Vector Box::operator[] (int i) const
{
  if (i == 0) return a;
  else return b;
}

//! Returns the center of the box.
inline Vector Box::Center() const
{
  return 0.5 * (a + b);
}

/*!
\brief Returns the diagonal of the box.
*/
inline Vector Box::Diagonal() const
{
  return (b - a);
}

/*!
\brief Compute the size (width, length and height) of a box.
\sa Box::Diagonal()
*/
inline Vector Box::Size() const
{
  return b - a;
}

/*!
\brief Returns the radius of the box, i.e. the length of the half diagonal of the box.
*/
inline double Box::Radius() const
{
  return 0.5 * Norm(b - a);
}

/*!
\brief Returns the k-th vertex of the box.

The returned vector is computed by analysing the first three bits of k as follows:
\code
Vector vertex=Vector((k&1)?b[0]:a[0],(k&2)?b[1]:a[1],(k&4)?b[2]:a[2]);
\endcode
*/
inline Vector Box::Vertex(int k) const
{
  return Vector((k & 1) ? b[0] : a[0], (k & 2) ? b[1] : a[1], (k & 4) ? b[2] : a[2]);
}

//! Compute the volume of a box.
inline double Box::Volume() const
{
  Vector side = b - a;
  return side[0] * side[1] * side[2];
}

/*!
\brief Compute the surface area of a box.
*/
inline double Box::Area() const
{
  Vector side = b - a;
  return 2.0 * (side[0] * side[1] + side[0] * side[2] + side[1] * side[2]);
}

/*!
\brief Check if an argument box is inside the box.
\param box The box.
*/
inline bool Box::Inside(const Box& box) const
{
  return ((a < box.a) && (b > box.b));
}

/*!
\brief Check if a point is inside the box.
\param p Point.
*/
inline bool Box::Inside(const Vector& p) const
{
  return ((a < p) && (b > p));
}

/*!
\brief Check if two boxes are (strictly) equal.
\param a, b Boxes.
*/
inline int operator==(const Box& a, const Box& b)
{
  return (a.a == b.a) && (a.b == b.b);
}

/*!
\brief Check if two boxes are (strictly) different.
\param a, b Boxes.
*/
inline int operator!=(const Box& a, const Box& b)
{
  return !(a == b);
}
