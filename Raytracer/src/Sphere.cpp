#pragma once
//#include "stdafx.h"
#include "Sphere.h"
#include "Vector.h"
#include "Maths.h"
#include <iostream>
//#include "Renderable.h"

Sphere::Sphere(Vector pos, Colour colour, float rad)
{
	mType = "Sphere";
	mPosition = pos;
	mRadius = rad;
	mColour = colour;
}
Sphere::Sphere()
{
	mType = "Sphere";
}


bool Sphere::Intersects(Fragment& fragment)
{
	
	// https://www.youtube.com/watch?v=HFPlKQGChpE //how to do the intersection	
	float tempT = fragment.getT();//This stores the current value of t just incase the old value is close to the camera than the one we'll calculate next

	Vector rayOrigin = fragment.getRay().GetOrigin();//point the ray is fired from
	Vector rayDirection = fragment.getRay().GetDirection();

	Vector OriginToSphereCentre = mPosition - rayOrigin;//Vector to the centre of the sphere from the rays origin

	fragment.setT( Maths::dot(OriginToSphereCentre, rayDirection));// this t is the point such that the vector to the sphere centre is perpendicular to the ray

	float y = (mPosition - (rayOrigin + (rayDirection * fragment.getT()))).getMagnitude();//y value in the equation of a circle.

	if (y < mRadius)
	{
		float x = sqrt(mRadius * mRadius - y*y);

		float t1 = fragment.getT() - x; float t2 = fragment.getT() + x;

		if (t1 < t2)//if t1 < t2, we know the point of intersection t1 units down the ray is the closer point to the camera
		{
			if (t1 < tempT)//we now need to know if t1 is closer than the closest other known object to the camera
			{
				fragment.setT(t1);

				Vector hitPoint = (rayOrigin + (rayDirection * t1));//point of intersection on the sphere
				Vector normal =	this->GetNormal(hitPoint);//Normal at that point
				Vector reflectedVector = hitPoint - (normal * (2 * ((hitPoint.dot(normal))/(normal.dot(normal)))));

				return true;
			}
		}
		else//else, we know the point of intersection t2 units down the ray is the closer point to the camera
		{
			if (t2 < tempT)//we now need to know if t2 is closer than the closest other known object to the camera
			{
				fragment.setT(t2);

				Vector hitPoint = (rayOrigin + (rayDirection * t1));//point of intersection on the sphere
				Vector normal = this->GetNormal(hitPoint);//Normal at that point
				Vector reflectedVector = hitPoint - (normal * (2 * ((hitPoint.dot(normal)) / (normal.dot(normal)))));


				return true;
			}
		}
	}

	fragment.setT(tempT);
	return false;
	
	
	/*
	//More optimised way, idk how it works. Also isn't correct
	float tempt = t;


	Vector rayOrigin = ray.GetOrigin();//pos
	Vector rayDirection = ray.GetDirection();//dir
	Vector oc = rayOrigin - mPosition ;//I think the vector pointing to the impact point
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
		if (t < tempt)
		{
			//Vector hitPoint = (rayOrigin + (rayDirection * t));//point of intersection on the sphere
			//Vector normal =	this->GetNormal(hitPoint);//Normal at that point
			//Vector reflectedVector = hitPoint - (normal * (2 * ((hitPoint.dot(normal))/(normal.dot(normal)))));


		}
			return true;

		t = tempt;
		return false;
	}
	*/
	
}

std::string Sphere::GetType()
{
	return mType;
}

float Sphere::GetRadius()
{
	return mRadius;
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
float Sphere::getSize()
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
void Sphere::setSize(float rad)
{
	mRadius = rad;
}