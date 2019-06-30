#pragma once
#include "Maths\Vector.h"
class Ray
{
	public:
		Ray(Vector origin, Vector direction);
		Vector GetOrigin();
		Vector GetDirection();



	private:
		Vector mOrigin; //origin
		Vector mDirection; //direction
};