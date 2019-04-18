#pragma once
//#include "stdafx.h"
#include"Ray.h"
#include"Vector.h"
Ray::Ray(Vector i, Vector j)
{
	mOrigin = i; mDirection = j;
}

Vector Ray::GetOrigin()
{
	return mOrigin;
}

Vector Ray::GetDirection()
{
	return mDirection;
}