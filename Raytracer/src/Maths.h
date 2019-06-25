#pragma once
#include <cmath>
#include "Vector.h"


class Maths
{
	public:
		float static dot(Vector v, Vector b);
		float static getDistance(Vector away, Vector home);
		Vector static Normalise(Vector a);
		float static GetMagnitude(Vector a);
		float static GetMagnitude(float a);
		float static degToRad(double degrees);
		float static radToDeg(double radians);
	private:
};