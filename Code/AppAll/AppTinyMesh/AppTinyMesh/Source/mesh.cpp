#include "mesh.h"

/*!
\class Mesh mesh.h

\brief Core triangle mesh class.
*/

/*!
\brief Initialize the mesh to empty.
*/
Mesh::Mesh()
{
}

/*!
\brief Initialize the mesh from a list of vertices and a list of triangles.

Indices must have a size multiple of three (three for triangle vertices and three for triangle normals).

\param vertices List of geometry vertices.
\param indices List of indices wich represent the geometry triangles.
*/
Mesh::Mesh(const QVector<Vector>& vertices, const QVector<int>& indices) :vertices(vertices), varray(indices)
{
  normals.reserve(vertices.size());
  normals.fill(Vector::Z);
}

/*!
\brief Create the mesh.

\param vertices Array of vertices.
\param normals Array of normals.
\param va, na Array of vertex and normal indexes.
*/
Mesh::Mesh(const QVector<Vector>& vertices, const QVector<Vector>& normals, const QVector<int>& va, const QVector<int>& na) :vertices(vertices), normals(normals), varray(va), narray(na)
{
}

/*!
\brief Reserve memory for arrays.
\param nv,nn,nvi,nvn Number of vertices, normals, vertex indexes and vertex normals.
*/
void Mesh::Reserve(int nv, int nn, int nvi, int nvn)
{
  vertices.reserve(nv);
  normals.reserve(nn);
  varray.reserve(nvi);
  narray.reserve(nvn);
}

/*!
\brief Empty
*/
Mesh::~Mesh()
{
}

/*!
\brief Smooth the normals of the mesh.

This function weights the normals of the faces by their corresponding area.
\sa Triangle::AreaNormal()
*/
void Mesh::SmoothNormals()
{
  // Set size
  normals.resize(vertices.size());

  // Initialize 
  normals.fill(Vector(0.0), vertices.size());

  narray = varray;

  // Accumulate normals
  for (int i = 0; i < varray.size(); i += 3)
  {
    Vector tn = Triangle(vertices[varray.at(i)], vertices[varray.at(i + 1)], vertices[varray.at(i + 2)]).AreaNormal();
    normals[narray[i + 0]] += tn;
    normals[narray[i + 1]] += tn;
    normals[narray[i + 2]] += tn;
  }

  // Normalize 
  for (int i = 0; i < normals.size(); i++)
  {
    Normalize(normals[i]);
  }
}

/*!
\brief Check if the i<sup>th</sup> triangle in the mesh is a flat or smooth triangle.

This is performed by comparing the indexes of the normals, not the normals themselves.
Therefore, should the normal indexes be different but the normal vector equal, the
function will return that the triangle is a smooth one anyway.
\param i Index of the triangle.
*/
int Mesh::IsSmooth(int i) const
{
  return !((narray[i * 3] == narray[i * 3 + 1]) && (narray[i * 3] == narray[i * 3 + 2]));
}

/*!
\brief Add a smooth triangle to the geometry.
\param a, b, c Index of the vertices.
\param na, nb, nc Index of the normals.
*/
void Mesh::AddSmoothTriangle(int a, int na, int b, int nb, int c, int nc)
{
  varray.append(a);
  narray.append(na);
  varray.append(b);
  narray.append(nb);
  varray.append(c);
  narray.append(nc);
}

/*!
\brief Add a triangle to the geometry.
\param a, b, c Index of the vertices.
\param n Index of the normal.
*/
void Mesh::AddTriangle(int a, int b, int c, int n)
{
  varray.append(a);
  narray.append(n);
  varray.append(b);
  narray.append(n);
  varray.append(c);
  narray.append(n);
}


/*!
\brief Add a smmoth quadrangle to the geometry.

Creates two smooth triangles abc and acd.

\param a, b, c, d  Index of the vertices.
\param na, nb, nc, nd Index of the normal for all vertices.
*/
void Mesh::AddSmoothQuadrangle(int a, int na, int b, int nb, int c, int nc, int d, int nd)
{
  // First triangle
  AddSmoothTriangle(a, na, b, nb, c, nc);

  // Second triangle
  AddSmoothTriangle(a, na, c, nc, d, nd);
}

/*!
\brief Add a quadrangle to the geometry.

\param a, b, c, d  Index of the vertices and normals.
*/
void Mesh::AddQuadrangle(int a, int b, int c, int d)
{
  AddSmoothQuadrangle(a, a, b, b, c, c, d, d);
}

/*!
\brief Compute the bounding box of the object.
*/
Box Mesh::GetBox() const
{
  if (vertices.size() == 0)
  {
    return Box::Null;
  }
  return Box(vertices);
}

/*
\brief Check if a point is inside or outside of the object.

This is a brute force algorithm, that computes all the intersections between the ray and the triangles of the object.

The mesh should be closed, i.e. without holes.
\param p Point.
*/
bool Mesh::Inside(const Vector& p) const
{
  // Ray used for intersecting the triangles
  const Ray ray(p, Vector(1.0, 0.0, 0.0));
  bool check = false;

  for (int i = 0; i < varray.size() / 3; i++)
  {
    // Temporary depth
    double t;
    double u, v;
    // Edge
    if (GetTriangle(i).Intersect(ray, t,u,v))
    {
      if (t >= 0.0) check = !check;
    }
  }

  return check;
}

/*!
\brief Creates an axis aligned box.

The object has 8 vertices, 6 normals and 12 triangles.
\param box The box.
*/
Mesh::Mesh(const Box& box)
{
  // Vertices
  vertices.resize(8);

  for (int i = 0; i < 8; i++)
  {
    vertices[i] = box.Vertex(i);
  }

  // Normals
  normals.append(Vector(-1, 0, 0));
  normals.append(Vector(1, 0, 0));
  normals.append(Vector(0, -1, 0));
  normals.append(Vector(0, 1, 0));
  normals.append(Vector(0, 0, -1));
  normals.append(Vector(0, 0, 1));

  // Reserve space for the triangle array
  varray.reserve(12 * 3);
  narray.reserve(12 * 3);

  AddTriangle(0, 2, 1, 4);
  AddTriangle(1, 2, 3, 4);

  AddTriangle(4, 5, 6, 5);
  AddTriangle(5, 7, 6, 5);

  AddTriangle(0, 4, 2, 0);
  AddTriangle(4, 6, 2, 0);

  AddTriangle(1, 3, 5, 1);
  AddTriangle(3, 7, 5, 1);

  AddTriangle(0, 1, 5, 2);
  AddTriangle(0, 5, 4, 2);

  AddTriangle(3, 2, 7, 3);
  AddTriangle(6, 7, 2, 3);
}


#include <QtCore/QFile>
#include <QtCore/QTextStream>

/*!
\brief Import a mesh from an .obj file.
\param filename File name.
*/
void Mesh::Load(const QString& filename)
{
  vertices.clear();
  normals.clear();
  varray.clear();
  narray.clear();

  QFile data(filename);

  if (!data.open(QFile::ReadOnly))
    return;
  QTextStream in(&data);

  // Set of regular expressions : Vertex, Normal, Triangle
  QRegExp rexv("v\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)");
  QRegExp rexn("vn\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)");
  QRegExp rext("f\\s*(\\d*)/\\d*/(\\d*)\\s*(\\d*)/\\d*/(\\d*)\\s*(\\d*)/\\d*/(\\d*)");
  while (!in.atEnd())
  {
    QString line = in.readLine();
    if (rexv.indexIn(line, 0) > -1)
    {
      Vector q = Vector(rexv.cap(1).toDouble(), rexv.cap(2).toDouble(), rexv.cap(3).toDouble()); vertices.append(q);
    }
    else if (rexn.indexIn(line, 0) > -1)
    {
      Vector q = Vector(rexn.cap(1).toDouble(), rexn.cap(2).toDouble(), rexn.cap(3).toDouble());  normals.append(q);
    }
    else if (rext.indexIn(line, 0) > -1)
    {
      varray.append(rext.cap(1).toInt() - 1);
      varray.append(rext.cap(3).toInt() - 1);
      varray.append(rext.cap(5).toInt() - 1);
      narray.append(rext.cap(2).toInt() - 1);
      narray.append(rext.cap(4).toInt() - 1);
      narray.append(rext.cap(6).toInt() - 1);
    }
  }
  data.close();
}

/*!
\brief Translate the mesh.
\param t Translation vector.
*/
void Mesh::Translate(const Vector& t)
{
  // Vertexes
  for (int i = 0; i < vertices.size(); i++)
  {
    vertices[i] += t;
  }
}

/*!
\brief Scale the mesh.
\param s Scaling factor.
*/
void Mesh::Scale(double s)
{
  // Vertexes
  for (int i = 0; i < vertices.size(); i++)
  {
    vertices[i] *= s;
  }

  if (s < 0.0)
  {
    // Normals
    for (int i = 0; i < normals.size(); i++)
    {
      normals[i] = -normals[i];
    }
  }
}

/*!
\brief Save the mesh in .obj format, with vertices and normals.
\param url Filename.
\param meshName %Mesh name in .obj file.
*/
void Mesh::SaveObj(const QString& url, const QString& meshName) const
{
  QFile data(url);
  if (!data.open(QFile::WriteOnly))
    return;
  QTextStream out(&data);
  out << "g " << meshName << endl;
  for (int i = 0; i < vertices.size(); i++)
    out << "v " << vertices.at(i)[0] << " " << vertices.at(i)[1] << " " << vertices.at(i)[2] << QString('\n');
  for (int i = 0; i < normals.size(); i++)
    out << "vn " << normals.at(i)[0] << " " << normals.at(i)[1] << " " << normals.at(i)[2] << QString('\n');
  for (int i = 0; i < varray.size(); i += 3)
  {
    out << "f " << varray.at(i) + 1 << "//" << narray.at(i) + 1 << " "
      << varray.at(i + 1) + 1 << "//" << narray.at(i + 1) + 1 << " "
      << varray.at(i + 2) + 1 << "//" << narray.at(i + 2) + 1 << " "
      << "\n";
  }
  out.flush();
  data.close();
}