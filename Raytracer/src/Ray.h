#pragma once
#include "Vector.h"
class Ray
{
	public:
		Ray(Vector i, Vector j);
		Vector GetOrigin();
		Vector GetDirection();



	private:
		Vector mOrigin; //origin
		Vector mDirection; //direction
};