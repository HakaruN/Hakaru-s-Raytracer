#pragma once
//#include "stdafx.h"
#include "Maths.h"

float Maths::dot(Vector a, Vector b) {return (a.GetX() * b.GetX()) + (a.GetY() * b.GetY()) + (a.GetZ() * b.GetZ());}

float Maths::getDistance(Vector away, Vector home)
{
	return sqrt(pow(home.GetX() - away.GetX(), 2) + pow( home.GetY() - away.GetY(), 2) + pow(home.GetZ() - away.GetZ(),2));
}

float Maths::GetMagnitude(float a)
{
	return sqrt(pow(a, 2));
}
float Maths::GetMagnitude(Vector a)
{
	return sqrt((pow(a.GetX(),2)) + (pow(a.GetY(), 2)) + (pow(a.GetZ(), 2)));
}
Vector Maths::Normalise(Vector a)
{
	return Vector(sqrt(pow(a.GetX(), 2)), sqrt(pow(a.GetY(), 2)), sqrt(pow(a.GetZ(), 2)));
}
float Maths::degToRad(double degrees) 
{
	return(degrees * (3.1415 / 180));//radians = degrees  * pi / 180
}
float Maths::radToDeg(double radians)
{
	return(radians * (180 / 3.1415 ));//radians = degrees  * 180 / pi
}