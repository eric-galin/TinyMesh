// Camera

#include "camera.h"

/*!
\class Camera camera.h
\brief Core camera class.
*/

/*!
\brief Create a default camera.
*/
Camera::Camera() :Camera(Vector::Null, Vector::Y, Vector::Z, 1.0, 1.0, 1.0, 1000.0)
{
}

/*!
\brief Create a camera given its location and look-at point.

If no upward vector is provided, it is internally defined as z-axis.

The view vector is defined as the vector between the eye point and the look at point.
The right vector, which is always computed as a cross product between the view vector and the up vector.
\param eye Eye point.
\param at Look-at point.
\param up Up vector.
\param width, height Width and height of virtual screen.
\param near, far Near and far planes.
*/
Camera::Camera(const Vector& eye, const Vector& at, const Vector& up, double width, double height, double near, double far) :eye(eye), at(at), up(up)
{
  Camera::width = width;
  Camera::height = height;

  // Near and far planes 
  Camera::nearplane = near;
  Camera::farplane = far;

  // Aperture
  Camera::cah = 0.980;
  Camera::cav = 0.735;
  Camera::fl = 35.0;
}

/*!
\brief Create a camera given its location and look at point.
\param eye Eye point.
\param at Look-at point.
\param up Up vector.
\param field Field of view, should be in [0,Math::Pi/2.0].
\param near, far Near and far planes.
*/
Camera::Camera(const Vector& eye, const Vector& at, const Vector& up, double field, double near, double far) :Camera(eye, at, up, sin(field / 2.0), sin(field / 2.0), near, far)
{
}

/*!
\brief Overloaded.
\param s Stream.
\param camera The camera.
*/
std::ostream& operator<<(std::ostream& s, const Camera& camera)
{
  s << "Camera(" << camera.eye << ',' << camera.at << ',' << camera.width << ',' << camera.height << ',' << camera.up << ')' << std::endl;
  return s;
}

/*!
\brief Reset the camera so that the up vector should point to the sky.
*/
void Camera::Vertical()
{
  up = Vector::Z;

  Vector z = at - eye;
  double length = Norm(z);

  Vector left = up / z;
  z = left / up;
  z /= Norm(z);

  at = eye + z * length;
}

/*!
\brief Moves the eye point towards or away from the look at point.

The look-at point does not change.

\param a Distance.
\param t Boolean, set to true if look-at point should also be moved in the direction.
*/
void Camera::BackForth(double a, bool t)
{
  Vector z = at - eye;
  double length = Norm(z);
  z /= length;

  eye += a * z;
  if (t == true)
  {
    at += a * z;
  }
}

/*!
\brief Rotates the camera relatively to the look-at point.
\param a Distance.
*/
void Camera::LeftRightRound(double a)
{
  Vector e = eye - at;
  Vector left = up / e;
  e = Vector(e[0] * cos(a) - e[1] * sin(a), e[0] * sin(a) + e[1] * cos(a), e[2]);
  left = Vector(left[0] * cos(a) - left[1] * sin(a), left[0] * sin(a) + left[1] * cos(a), 0.0);
  up = Normalized(left / -e);
  eye = at + e;
}

/*!
\brief Rotates the camera relatively to the look-at point.
\param a Distance.
*/
void Camera::UpDownRound(double a)
{
  Vector z = at - eye;
  double length = Norm(z);
  z /= length;
  Vector left = up / z;
  left /= Norm(left);

  // Rotate
  z = z * cos(a) + up * sin(a);

  // Update Vector
  up = z / left;
  eye = at - z * length;
}

/*!
\brief Moves the camera left or right, preserving its height.
\param a Distance.
*/
void Camera::LeftRightHorizontal(double a)
{
  Vector z = at - eye;
  z[2] = 0.0;
  double length = Norm(z);
  z /= length;
  Vector left = Vector::Z / z;
  left /= Norm(left);

  eye += a * left;
  at += a * left;
}

/*!
\brief Moves the camera vertically.

This function keeps the left vector horizontal.
\param a Distance.
*/
void Camera::UpDownVertical(double a)
{
  Vector z = at - eye;
  double length = Norm(z);
  z /= length;
  Vector left = Vector::Z / z;
  left /= Norm(left);

  eye += a * z / left;
  at += a * z / left;
}

/*!
\brief Returns the horizontal angle of view.

Angle is in radian.
*/
double Camera::GetAngleOfViewH() const
{
  // Horizontal angle of view in degrees 
  return 2.0 * atan(cah * 25.4 * 0.5 / fl);
}

/*!
\brief Returns the vertical angle of view.

Angle is in radian.

\param w, h Width and height of the screen
*/
double Camera::GetAngleOfViewV(double w, double h) const
{
  // Horizontal angle of view  
  double avh = GetAngleOfViewH();

  double avv = 2.0 * atan(tan(avh / 2.0) * double(h) / double(w));

  // Vertical angle of view
  return avv;
}

/*!
\brief Compute the equation of a ray given a pixel in the camera plane.
\param px,py Pixel coordinates.
\param w,h Size of the viewing window.
*/
Ray Camera::PixelToRay(int px, int py, int w, int h) const
{
  // Get coordinates
  Vector view = Normalized(At() - Eye());
  Vector horizontal = Normalized(view / Up());
  Vector vertical = Normalized(horizontal / view);

  double length = 1.0;

  // Convert to radians 
  double rad = GetAngleOfViewV(w, h);  // fov

  double vLength = tan(rad / 2.0) * length;
  double hLength = vLength * (double(w) / double(h));

  vertical *= vLength;
  horizontal *= hLength;

  // Translate mouse coordinates so that the origin lies in the center of the view port
  double x = px - w / 2.0;
  double y = h / 2.0 - py;

  // Scale mouse coordinates so that half the view port width and height becomes 1.0
  x /= w / 2.0;
  y /= h / 2.0;

  // Direction is a linear combination to compute intersection of picking ray with view port plane
  return Ray(eye, Normalized(view * length + horizontal * x + vertical * y));
}

/*!
\brief Compute coordinates of a point in the camera plane.
\param p Point.
\param u, v Coordinates in the screen
\param w, h Size of the viewing window.
*/
bool Camera::VectorToPixel(const Vector& p, double& u, double& v, int w, int h) const
{
  // Get coordinates
  const Vector view = Normalized(At() - Eye());
  const Vector horizontal = Normalized(view / Up());
  const Vector vertical = Normalized(horizontal / view);

  // Convert to radians 
  double rad = GetAngleOfViewV(w, h);  // fov

  double vLength = tan(rad / 2);
  double hLength = vLength * (double(w) / double(h));

  // Direction
  const Vector ep = p - Eye();
  u = horizontal * ep / vLength;
  v = vertical * ep / hLength;
  double z = view * ep;

  u /= z;
  v /= z;

  // Check if point lies outside of frustum
  if ((u < -1.0) || (u > 1.0) || (v < -1.0) || (v > 1.0) || (z < nearplane) || (z > farplane))
    return false;

  return true;
}

/*!
\brief Sets the camera target vector.
\param a Look-at point.
*/
void Camera::SetAt(const Vector& a)
{
  at = a;
  up = Vector::Z;
}

/*!
\brief Sets the camera eye point.
\param p Eye point.
*/
void Camera::SetEye(const Vector& p)
{
  eye = p;
}

/*!
\brief Get the near distance.
*/
double Camera::GetNear() const
{
  return nearplane;
}

/*!
\brief Get the far distance.
*/
double Camera::GetFar() const
{
  return farplane;
}

/*!
\brief Set the near and far planes.
\param n, f Near and far planes distance to th eye.
*/
void Camera::SetPlanes(double n, double f)
{
  nearplane = n;
  farplane = f;
}
