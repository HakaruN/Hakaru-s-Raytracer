#pragma once
//#include "stdafx.h"
#include"Ray.h"
#include"Vector.h"
Ray::Ray(Vector origin, Vector direction)
{
	mOrigin = origin; mDirection = direction;
}

Vector Ray::GetOrigin()
{
	return mOrigin;
}

Vector Ray::GetDirection()
{
	return mDirection;
}