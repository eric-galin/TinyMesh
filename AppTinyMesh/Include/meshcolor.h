#ifndef __MeshColor__
#define __MeshColor__

#include "color.h"
#include "mesh.h"

class MeshColor : public Mesh
{
protected:
  std::vector<Color> colors; //!< Array of colors.
  std::vector<int> carray;  //!< Indexes.

public:
  explicit MeshColor();
  explicit MeshColor(const Mesh&);
  explicit MeshColor(const Mesh&, const std::vector<Color>&, const std::vector<int>&);
  ~MeshColor();

  Color GetColor(int) const;
  std::vector<Color> GetColors() const;
  std::vector<int> ColorIndexes() const;
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
inline std::vector<Color> MeshColor::GetColors() const
{
  return colors;
}

/*!
\brief Return the set of color indices.
*/
inline std::vector<int> MeshColor::ColorIndexes() const
{
  return carray;
}

#endif
