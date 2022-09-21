#include "meshcolor.h"

/*!
\brief Create an empty mesh.
*/
MeshColor::MeshColor()
{
}

/*!
\brief Constructor from a Mesh with color array and indices.
\param m Base mesh.
\param cols Color array.
\param carr Color indexes, should be the same size as Mesh::varray and Mesh::narray.
*/
MeshColor::MeshColor(const Mesh& m, const std::vector<Color>& cols, const std::vector<int>& carr) : Mesh(m), colors(cols), carray(carr)
{
}

/*!
\brief Constructor from a Mesh.
\param m the base mesh
*/
MeshColor::MeshColor(const Mesh& m) : Mesh(m)
{
	colors.resize(vertices.size(), Color(1.0, 1.0, 1.0));
	carray = varray;
}

/*!
\brief Empty.
*/
MeshColor::~MeshColor()
{
}
