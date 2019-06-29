#pragma once
#include <cmath>
#include "Vector.h"


class Maths
{
public:
	inline static float dot(Vector& a, Vector& b) { return (a.GetX() * b.GetX()) + (a.GetY() * b.GetY()) + (a.GetZ() * b.GetZ()); }
	inline float static getDistance(Vector away, Vector home) { return sqrt(pow(home.GetX() - away.GetX(), 2) + pow(home.GetY() - away.GetY(), 2) + pow(home.GetZ() - away.GetZ(), 2)); }
	inline float static GetMagnitude(float a) { return sqrt(pow(a, 2)); }
	inline Vector static Normalise(Vector a) { return Vector(sqrt(pow(a.GetX(), 2)), sqrt(pow(a.GetY(), 2)), sqrt(pow(a.GetZ(), 2))); }

	inline float static GetMagnitude(Vector a) { return sqrt((pow(a.GetX(), 2)) + (pow(a.GetY(), 2)) + (pow(a.GetZ(), 2))); }
	inline double static degToRad(double degrees) { return(degrees * (3.1415 / 180)); }//radians = degrees  * pi / 180
	inline double static radToDeg(double radians){return(radians * (180 / 3.1415));}//radians = degrees  * 180 / pi
	private:
};