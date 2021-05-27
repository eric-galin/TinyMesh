#pragma once

#include "box.h"
#include "ray.h"
#include "mathematics.h"

// Triangle
class Triangle
{
protected:
	Vector p[3]; //!< Array of vertices.
public:
	//! Empty.
	Triangle() {}
	explicit Triangle(const Vector&, const Vector&, const Vector&);

	//! Empty.
	~Triangle() {}

	Vector operator[] (int) const;

	// Point in triangle
	Vector Vertex(double, double) const;

	// Intersection
	bool Intersect(const Ray&, double&, double&, double&) const;

	void Translate(const Vector&);

	// Geometry
	Vector Normal() const;
	Vector AreaNormal() const;
	Vector Center() const;

	double Area() const;
	double Aspect() const;
	Box GetBox() const;

	// Stream
	friend std::ostream& operator<<(std::ostream&, const Triangle&);

	double InscribedRadius() const;
	double CircumscribedRadius() const;
protected:
	static double epsilon; //!< Internal epsilon constant.
};

/*!
\brief Return the i-th vertex.
\param i Index.
*/
inline Vector Triangle::operator[] (int i) const
{
	return p[i];
}

//! Compute the barycenter of the triangle.
inline Vector Triangle::Center() const
{
	return (p[0] + p[1] + p[2]) / 3.0;
}

//! Compute the area of the triangle.
inline double Triangle::Area() const
{
	return 0.5 * Norm((p[0] - p[1]) / (p[2] - p[0]));
}

/*!
\brief Create a triangle.
\param a,b,c Vertices of the triangle.
*/
inline Triangle::Triangle(const Vector& a, const Vector& b, const Vector& c)
{
	p[0] = a;
	p[1] = b;
	p[2] = c;
}

class Mesh
{
protected:
	QVector<Vector> vertices; //!< Vertices.
	QVector<Vector> normals;  //!< Normals.
	QVector<int> varray;     //!< Vertex indexes.
	QVector<int> narray;     //!< Normal indexes.
public:
	explicit Mesh();
	explicit Mesh(const QVector<Vector>&, const QVector<int>&);
	explicit Mesh(const QVector<Vector>&, const QVector<Vector>&, const QVector<int>&, const QVector<int>&);
	~Mesh();

	void Reserve(int, int, int, int);

	Triangle GetTriangle(int) const;
	Vector Vertex(int) const;
	Vector Vertex(int, int) const;

	Vector Normal(int) const;

	int Triangles() const;
	int Vertexes() const;

	QVector<Vector> GetVertices() const;
	QVector<Vector> GetNormals() const;
	QVector<int> VertexIndexes() const;
	QVector<int> NormalIndexes() const;

	int VertexIndex(int, int) const;
	int NormalIndex(int, int) const;

	Vector operator[](int) const;

	bool Inside(const Vector&) const;

	Box GetBox() const;

	void Translate(const Vector&);
	void Scale(double);

	void SmoothNormals();
	int IsSmooth(int) const;

	// Constructors from core classes
	explicit Mesh(const Box&);

	void Load(const QString&);
	void SaveObj(const QString&, const QString&) const;
protected:
	void AddTriangle(int, int, int, int);
	void AddSmoothTriangle(int, int, int, int, int, int);
	void AddSmoothQuadrangle(int, int, int, int, int, int, int, int);
	void AddQuadrangle(int, int, int, int);
};

/*!
\brief Return the set of vertex indexes.
*/
inline QVector<int> Mesh::VertexIndexes() const
{
	return varray;
}

/*!
\brief Return the set of normal indexes.
*/
inline QVector<int> Mesh::NormalIndexes() const
{
	return narray;
}

/*!
\brief Get the vertex index of a given triangle.
\param t Triangle index.
\param i Vertex index.
*/
inline int Mesh::VertexIndex(int t, int i) const
{
	return varray.at(t * 3 + i);
}

/*!
\brief Get the normal index of a given triangle.
\param t Triangle index.
\param i Normal index.
*/
inline int Mesh::NormalIndex(int t, int i) const
{
	return narray.at(t * 3 + i);
}

/*!
\brief Get a triangle.
\param i Index.
\return The triangle.
*/
inline Triangle Mesh::GetTriangle(int i) const
{
	return Triangle(vertices.at(varray.at(i * 3 + 0)), vertices.at(varray.at(i * 3 + 1)), vertices.at(varray.at(i * 3 + 2)));
}

/*!
\brief Get a vertex.
\param i The index of the wanted vertex.
\return The wanted vertex (as a 3D Vector).
*/
inline Vector Mesh::Vertex(int i) const
{
	return vertices[i];
}

/*!
\brief Get a vertex from a specific triangle.
\param t The number of the triangle wich contain the wanted vertex.
\param v The triangle vertex: 0, 1, or 2.
\return The wanted vertex (as a 3D Vector).
*/
inline Vector Mesh::Vertex(int t, int v) const
{
	return vertices[varray[t * 3 + v]];
}

/*!
\brief Get the number of vertices in the geometry.
\return The number of vertices in the geometry, in other words the size of vertices.
*/
inline int Mesh::Vertexes() const
{
	return vertices.size();
}

/*!
\brief Get a normal.
\param i Index of the wanted normal.
\return The normal.
*/
inline Vector Mesh::Normal(int i) const
{
	return normals[i];
}

/*!
\brief Get the number of triangles.
*/
inline int Mesh::Triangles() const
{
	return varray.size() / 3;
}

/*!
\brief Get a vertex.
\param i The index of the wanted vertex.
\return The wanted vertex (as a 3D Vector).
\see vertex(int i) const
*/
inline Vector Mesh::operator[](int i) const
{
	return vertices[i];
}

/*!
\brief Get the array of vertices.
*/
inline QVector<Vector> Mesh::GetVertices() const
{
	return vertices;
}

/*!
\brief Get the array of normals.
*/
inline QVector<Vector> Mesh::GetNormals() const
{
	return normals;
}
