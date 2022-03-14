#ifndef __MeshColor__
#define __MeshColor__

#include "color.h"
#include "mesh.h"

class MeshColor : public Mesh
{
protected:
  QVector<Color> colors; //!< Array of colors.
  QVector<int> carray;  //!< Indexes.

public:
  explicit MeshColor();
  explicit MeshColor(const Mesh&);
  explicit MeshColor(const Mesh&, const QVector<Color>&, const QVector<int>&);
  ~MeshColor();

  Color GetColor(int) const;
  QVector<Color> GetColors() const;
  QVector<int> ColorIndexes() const;
};

/*!
\brief Get a color.
\param i The index of the desired color.
\return The color.
*/
inline Color MeshColor::GetColor(int i) const
{
  return colors[i];
}

/*!
\brief Get the array of colors.
*/
inline QVector<Color> MeshColor::GetColors() const
{
  return colors;
}

/*!
\brief Return the set of color indices.
*/
inline QVector<int> MeshColor::ColorIndexes() const
{
  return carray;
}

#endif
