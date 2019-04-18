#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Colour.h"
class Sphere
{
	public:
		Sphere();
		Sphere(Vector pos, float rad, Colour colour);
		 bool Intersects(Ray ray, float &t);
		Vector GetNormal(Vector point);
		Vector GetPos();
		Colour GetColour();
		void SetPos(Vector pos);
		void SetColour(Colour colour);
		void setRadius(float radius);

	private:
		Vector mPosition;//Sphere's position
		float mRadius;//Sphere's size
		Colour mColour;

};