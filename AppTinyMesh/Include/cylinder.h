#pragma once
// Cylinder

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Cylinder
{
protected:
	Vector a, b; //!< Lower and upper vertex.
	double r; //!< Cylinder radius
public:
	//! Empty.
	Cylinder() {}
	explicit Cylinder(const Vector&, const Vector&, const double r);

	//! Empty.
	~Cylinder() {}

	// Access vertexes
	Vector& operator[] (int);
	Vector operator[] (int) const;

	// Comparison
	friend int operator==(const Cylinder&, const Cylinder&);
	friend int operator!=(const Cylinder&, const Cylinder&);

	Vector Vertex(int) const;

	double Radius() const;

	// Translation, scale
	void Translate(const Vector&);
	void Scale(double);

	friend std::ostream& operator<<(std::ostream&, const Cylinder&);

public:
	static const double epsilon; //!< Internal \htmlonly\epsilon;\endhtmlonly for ray intersection tests.
};

//! Returns either end vertex of the cylinder.
inline Vector& Cylinder::operator[] (int i)
{
	if (i == 0) return a;
	else return b;
}

//! Overloaded.
inline Vector Cylinder::operator[] (int i) const
{
	if (i == 0) return a;
	else return b;
}

/*!
\brief Returns the radius of the cylinder, i.e. the length of the half diagonal of the cylinder.
*/
inline double Cylinder::Radius() const
{
	return 0.5 * r;
}

/*!
\brief Returns the k-th vertex of the cylinder.

The returned vector is computed by analysing the first three bits of k as follows:
\code
Vector vertex=Vector((k&1)?b[0]:a[0],(k&2)?b[1]:a[1],(k&4)?b[2]:a[2]);
\endcode
*/
inline Vector Cylinder::Vertex(int k) const
{
	return Vector((k & 1) ? b[0] : a[0], (k & 2) ? b[1] : a[1], (k & 4) ? b[2] : a[2]);
}

/*!
\brief Check if two cylinders are (strictly) equal.
\param a, b Cylinders.
*/
inline int operator==(const Cylinder& a, const Cylinder& b)
{
	return (a.a == b.a) && (a.b == b.b);
}

/*!
\brief Check if two cylinders are (strictly) different.
\param a, b Cylinders.
*/
inline int operator!=(const Cylinder& a, const Cylinder& b)
{
	return !(a == b);
}
