// Camera

#ifndef __Camera__
#define __Camera__

#include "box.h"
#include "ray.h"

// Implements a non-standard camera class
class Camera
{
protected:
  Vector eye;       //!< Eye.
  Vector at;        //!< Look at point.
  Vector up;        //!< Up vector.

  double width;     //!< Screen width.
  double height;    //!< Screen height.

  double cah;       //!< Camera aperture horizontal. 
  double cav;       //!< Camera aperture vertical.
  double fl;        //!< Focal length.

  double nearplane; //!< Near plane.
  double farplane;  //!< Far plane.
public:
  Camera();
  explicit Camera(const Vector&, const Vector&, const Vector & = Vector::Z, double = 1.0, double = 1.0, double = 1.0, double = 100000.0);
  explicit Camera(const Vector&, const Vector&, const Vector&, double, double = 1.0, double = 100000.0);

  Vector At() const;
  Vector Eye() const;
  Vector Up() const;
  Vector View() const;

  double GetNear() const;
  double GetFar() const;
  double GetAngleOfViewH() const;
  double GetAngleOfViewV(double, double) const;

  void Vertical();

  void BackForth(double, bool = false);
  void LeftRightRound(double);
  void UpDownRound(double);

  void SetAt(const Vector&);
  void SetEye(const Vector&);
  void SetPlanes(double, double);

  // Move camera in a plane
  void UpDownVertical(double);
  void LeftRightHorizontal(double);

  friend std::ostream& operator<<(std::ostream&, const Camera&);

  // Pixel and sub-pixel sampling
  Ray PixelToRay(int, int, int, int) const;
  bool VectorToPixel(const Vector&, double&, double&, int, int) const;
};

//! Returns the look-at point.
inline Vector Camera::At() const
{
  return at;
}

//! Returns the eye point.
inline Vector Camera::Eye() const
{
  return eye;
}

//! Returns the up point.
inline Vector Camera::Up() const
{
  return up;
}

/*!
\brief Returns the view direction.
*/
inline Vector Camera::View() const
{
  return at - eye;
}

#endif
