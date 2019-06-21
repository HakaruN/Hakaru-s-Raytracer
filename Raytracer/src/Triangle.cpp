//#include "stdafx.h"

#include"Triangle.h"
#include"Vector.h"
#include"Maths.h"
#include <iostream>


Triangle::Triangle(Vector position, Colour colour, Vector vert1, Vector vert2, Vector vert3)
{
	mPosition = position;
	
	mOrigVertices[0] = vert1;
	mOrigVertices[1] = vert2;
	mOrigVertices[2] = vert3;
	mVertices[0] = position + vert1;
	mVertices[1] = position + vert2;
	mVertices[2] = position + vert3;
	mColour = colour;
	

	maxDist = calcMaxDist();
	Colour darkWhite(128, 128, 128);
	Sphere mHitSphere(mPosition, darkWhite, maxDist);
}

Colour Triangle::GetColour()
{
	return mColour;
}
Vector Triangle::GetPos()
{
	return mPosition;
}
void Triangle::SetPos(Vector pos)
{

	mPosition = pos;
	mVertices[0] = mPosition + mOrigVertices[0];
	mVertices[1] = mPosition + mOrigVertices[1];
	mVertices[2] = mPosition + mOrigVertices[2];

	maxDist = calcMaxDist();
	Colour darkWhite(128, 128, 128);
	Sphere mHitSphere(mPosition, darkWhite, maxDist);

}


float Triangle::calcMaxDist()
{
	if (Vector::distanceBetweenVectors(mVertices[0], mPosition) > maxDist)
	{
		maxDist = Vector::distanceBetweenVectors(mVertices[0], mPosition);
	}
	else if (Vector::distanceBetweenVectors(mVertices[1], mPosition) > maxDist)
	{
		maxDist = Vector::distanceBetweenVectors(mVertices[1], mPosition);
	}
	else if (Vector::distanceBetweenVectors(mVertices[2], mPosition) > maxDist)
	{
		maxDist = Vector::distanceBetweenVectors(mVertices[2], mPosition);
	}
	return maxDist;
}
void Triangle::SetColour(Colour colour)
{
	mColour = colour;
}

Vector Triangle::GetNormal(Vector point)
{
	return ((mVertices[2] - mVertices[0]).cross((mVertices[1] - mVertices[0]))) / (Maths::GetMagnitude((mVertices[2] - mVertices[0]).cross((mVertices[1] - mVertices[0]))));
}

bool Triangle::Intersects(Ray ray, float &t)
{

	if (1)
	//if (mHitSphere.Intersects(ray, t))
	{
		Vector normalVec = Triangle::GetNormal(Vector(0, 0, 0));
		Vector rayOrigin = ray.GetOrigin();
		Vector rayDirection = ray.GetDirection();

		//first need to calculate how far along the ray is the intersectionpoint of the plane
		float d = normalVec.dot(mVertices[0]);
		t = ((normalVec.dot(rayOrigin)) + d) / normalVec.dot(rayDirection);

		if (t < 0)
			return false;//triangle is behind camera


		//compute intersection point using the ray formula
		Vector p = rayOrigin + (rayDirection * t);


		//inside out test
		Vector edge0 = mVertices[1] - mVertices[0];
		Vector vp0 = p - mVertices[0];
		Vector c = edge0.cross(vp0);
		if (normalVec.dot(c) < 0)
			return false;

		Vector edge1 = mVertices[2] - mVertices[1];
		Vector vp1 = p - mVertices[1];
		c = edge1.cross(vp1);
		if (normalVec.dot(c) < 0)
			return false;

		Vector edge3 = mVertices[0] - mVertices[2];
		Vector vp2 = p - mVertices[2];
		c = edge3.cross(vp2);
		if (normalVec.dot(c) < 0)
			return false;

		return true;
	}
	else
	{
		return false;
	}
}

float Triangle::GetViewableArea(Vector toCamera) {
	return 0;
}