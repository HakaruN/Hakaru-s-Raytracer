#pragma once
//#include "stdafx.h"
#include "Vector.h"	

//float mX, myY, mzZ;
	Vector::Vector() { mX = mY = mZ = 0; }
	Vector::Vector(float x, float y, float z) { mX = x, mY = y, mZ = z; }
	float Vector::GetX(){return mX;}
	float Vector::GetY() { return mY; }
	float Vector::GetZ() { return mZ; }
