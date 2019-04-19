#pragma once
#include "Vector.h"
#include "Colour.h"
class Renderable//abstract class for the renderable objects to inherit from
{
	public:

		
		virtual bool Intersects(Ray ray, float &t) = 0;
		virtual void SetPos(Vector pos) = 0;
		virtual void SetColour(Colour colour) = 0;
		virtual Vector GetNormal(Vector point) = 0;
		virtual Vector GetPos() = 0;
		virtual Colour GetColour() = 0;

	protected:
		Vector mPosition;//Sphere's position
		Colour mColour;
};