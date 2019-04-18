#pragma once
//#include "stdafx.h"
#include "Maths.h"

float Maths::dot(Vector a, Vector b) {return (a.GetX() * b.GetX()) + (a.GetY() * b.GetY()) + (a.GetZ() * b.GetZ());}

float Maths::getDistance(Vector away, Vector home)
{
	return sqrt(pow(home.GetX() - away.GetX(), 2) + pow( home.GetY() - away.GetY(), 2) + pow(home.GetZ() - away.GetZ(),2));
}