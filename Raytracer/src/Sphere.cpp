#pragma once
//#include "stdafx.h"
#include "Sphere.h"
#include "Vector.h"
#include "Maths.h"
//#include "Renderable.h"

Sphere::Sphere(Vector pos, Colour colour, float rad)
{
	mPosition = pos;
	mRadius = rad;
	mColour = colour;
}
Sphere::Sphere()
{
}


bool Sphere::Intersects(Ray ray, float &t)
{
	 // Point intersection p = pos + dir * t where t = distance along the ray
	Vector rayOrigin = ray.GetOrigin();//pos
	Vector rayDirection = ray.GetDirection();//dir
	Vector oc = rayOrigin - mPosition;
	float b = 2 * Maths::dot(oc, rayDirection);
	float c = Maths::dot(oc, oc ) - pow(mRadius, 2);
	float discriminant = pow(b,2) - 4 * c;
	if (discriminant < 0) return false; //if the discriminant > 0, the quadratic equation has 2 roots
	else
	{
		discriminant = sqrt(discriminant);
		float t0 = -b - discriminant;
		float t1 = -b + discriminant;

		t = (t0 < t1) ? t0 : t1;//if t0 = t1 then the ray hit tangent to the sphere
		return true;
	}
}


float Sphere::GetRadius()
{
	return mRadius;
}
Vector Sphere::GetNormal(Vector point)
{
	return (point - mPosition) / mRadius;
}
Vector Sphere::GetPos()
{
	return mPosition;
}
Colour Sphere::GetColour()
{
	return mColour;
}
float Sphere::GetViewableArea(Vector toCamera)
{
	return 3.14 * mRadius * mRadius;
}

void Sphere::SetPos(Vector pos)
{
	mPosition = pos;
}
void Sphere::SetColour(Colour colour)
{
	mColour = colour;
}
void Sphere::setRadius(float radius)
{
	mRadius = radius;
}