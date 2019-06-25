#pragma once
#include <cmath>
#include "Vector.h"


class Maths
{
	public:
		inline static float dot(Vector& a, Vector& b) { return (a.GetX() * b.GetX()) + (a.GetY() * b.GetY()) + (a.GetZ() * b.GetZ()); }
		float static getDistance(Vector away, Vector home);
		Vector static Normalise(Vector a);
		float static GetMagnitude(Vector a);
		float static GetMagnitude(float a);
		float static degToRad(double degrees);
		float static radToDeg(double radians);
	private:
};