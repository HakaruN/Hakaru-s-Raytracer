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
Sphere::Sphere() : Renderable()
{
}

 bool Sphere::Intersects(Ray ray, float &t)
{
	Vector rayOrigin = ray.GetOrigin();
	Vector rayDirection = ray.GetDirection();
	Vector oc = rayOrigin - mPosition;
	float b = 2 * Maths::dot(oc, rayDirection);
	float c = Maths::dot(oc, oc ) - pow(mRadius, 2);
	float disc = b * b - 4 * c;
	if (disc < 0) return false;
	else
	{
		disc = sqrt(disc);
		float t0 = -b - disc;
		float t1 = -b + disc;

		t = (t0 < t1) ? t0 : t1;
		return true;
	}

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
float Sphere::GetRadius()
{
	return mRadius;
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