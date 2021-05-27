// Triangle

#include "mesh.h"

double Triangle::epsilon = 1.0e-7;

/*!
\class Triangle triangle.h
\brief Base minimum storage triangle class.

The data-structure of the triangle does not include the normalized normal vector.
*/

/*!
\brief Compute a point in the triangle, given uv-coordinates.
\param u,v Coordinates.
*/
Vector Triangle::Vertex(double u, double v) const
{
  return p[0] + u * (p[1] - p[0]) + v * (p[2] - p[0]);
}

/*!
\brief Compute the normal vector of the triangle.

This function is expensive as it requires normalizing the cross product of the edge vectors.
\sa TriangleEdge
*/
Vector Triangle::Normal() const
{
  return Normalized((p[1] - p[0]) / (p[2] - p[0]));
}

/*!
\brief Compute the normal vector of the triangle, and scale the normal using its area.

This function is less expensive than Triangle::Normal() as it does not require normalizing the cross product of the edge vectors.

IIt is useful for computing the vertex normals of a triangle mesh by averaging the face normals of the triangles and weighting
the influence of the different triangles with their area.
\sa Triangle::Normal()
*/
Vector Triangle::AreaNormal() const
{
  return 0.5 * ((p[1] - p[0]) / (p[2] - p[0]));
}

/*!
\brief Compute the intersection between a ray and a triangle.

Return the barycentric coordinates of the intersection
if within the triangle.

After Tomas Moller and Ben Trumbore,
<I>Fast, minimum storage ray-triangle intersection</I>,
<B>Journal of graphics tools</B>, 2(1):21-28, 1997.

\param ray The ray (direction should be of unit length).
\param t Intersection depth.
\param u,v Parametric coordinates of the intersection depth in the triangle.
*/
bool Triangle::Intersect(const Ray& ray, double& t, double& u, double& v) const
{
  Vector e[2];

  // Find edge vectors
  e[0] = p[1] - p[0];
  e[1] = p[2] - p[0];

  Vector pvec = ray.Direction() / e[1];

  // Determinant, if determinant is near zero, ray lies in plane of triangle
  double det = e[0] * pvec;

  if ((det > -epsilon) && (det < epsilon))
    return false;
  det = 1.0 / det;

  // calculate distance from first vertex to ray origin
  Vector tvec = ray.Origin() - p[0];

  // calculate U parameter and test bounds
  u = (tvec * pvec) * det;
  if ((u < 0.0) || (u > 1.0))
    return false;

  // calculate V parameter and test bounds
  Vector qvec = tvec / e[0];

  v = (ray.Direction() * qvec) * det;
  if ((v < 0.0) || (u + v) > 1.0)
    return false;

  // Ray intersects triangle
  t = (e[1] * qvec) * det;
  return true;
}

/*!
\brief Translates a triangle by a given vector.

\param u Translation vector.
*/
void Triangle::Translate(const Vector& u)
{
  for (int i = 0; i < 3; i++)
  {
    p[i] += u;
  }
}

/*!
\brief Computes the axis aligned box enclosing the triangle.
*/
Box Triangle::GetBox() const
{
  return Box(Vector::Min(Vector::Min(p[0], p[1]), p[2]), Vector::Max(Vector::Max(p[0], p[1]), p[2]));
}

/*!
\brief Compute the radius of the circle inscribed in the
triangle.

Some algebra will show that it is half the ratio
of the half perimeter and the surface of the triangle.
*/
double Triangle::InscribedRadius() const
{
  Vector u = p[0] - p[1];
  Vector v = p[2] - p[0];
  Vector w = p[1] - p[2];
  double a = Norm(u) + Norm(v) + Norm(w);
  double s = Norm(u / v);
  return s / a;
}

/*!
\brief Compute the radius of the circumscribed circle of the triangle.
*/
double Triangle::CircumscribedRadius() const
{
  double u = Norm(p[0] - p[1]);
  double v = Norm(p[1] - p[2]);
  double w = Norm(p[2] - p[0]);
  return u * v * w / sqrt((u + v + w) * (-u + v + w) * (u - v + w) * (u + v - w));
}

/*!
\brief Computes the aspect ratio of the triangle.

It is defined as the radius of the inscribed circle divided by the radius of the
circumscribing circle. This function is faster than:

\code
Triangle t;
double a=2.0*t.InscribedRadius()/t.CircumscribedRadius();
\endcode
*/
double Triangle::Aspect() const
{
  double ab = Norm(p[1] - p[0]);
  double bc = Norm(p[2] - p[1]);
  double ca = Norm(p[0] - p[2]);

  double s = 0.5 * (ab + bc + ca);

  double u = (s - ab) * (s - bc) * (s - ca);

  return 8.0 * u / (ab * bc * ca);
}

/*!
\brief Overloaded.
\param t %Triangle.
\param s Stream.
*/
std::ostream& operator<<(std::ostream& s, const Triangle& t)
{
  s << "Triangle(" << t.p[0] << ',' << t.p[1] << ',' << t.p[2] << ')';
  return s;
}
