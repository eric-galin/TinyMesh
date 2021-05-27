#pragma once

class Math
{
public:
	static double Clamp(double, double = 0.0, double = 1.0);

	// Minimum and maximum
	static double Min(double, double);
	static double Max(double, double);
	static double Min(double, double, double);
	static double Max(double, double, double);

	static constexpr double DegreeToRadian(double);
	static constexpr double RadianToDegree(double);
};

/*!
\brief Clamp a double value between two bounds.
\param x Input value.
\param a, b Lower and upper bounds.
*/
inline double Math::Clamp(double x, double a, double b)
{
	return (x < a ? a : (x > b ? b : x));
}

/*!
\brief Minimum of two reals.
\param a, b Real values.
*/
inline double Math::Min(double a, double b)
{
	return (a < b ? a : b);
}

/*!
\brief Maximum of two reals.
\param a, b Real values.
*/
inline double Math::Max(double a, double b)
{
	return (a > b ? a : b);
}

/*!
\brief Maximum of three reals.
\param a, b, c Real values.
*/
inline double Math::Max(double a, double b, double c)
{
	return Math::Max(Math::Max(a, b), c);
}

/*!
\brief Minimum of three reals.
\param a, b, c Real values.
*/
inline double Math::Min(double a, double b, double c)
{
	return Math::Min(Math::Min(a, b), c);
}

/*!
\brief Convert degrees to randians.
\param a Angle in degrees.
*/
inline constexpr double Math::DegreeToRadian(double a)
{
	return a * 3.14159265358979323846 / 180.0;
}

/*!
\brief Convert radian to degrees.
\param a Angle in radian.
*/
inline constexpr double Math::RadianToDegree(double a)
{
	return a * 180.0 / 3.14159265358979323846;
}
