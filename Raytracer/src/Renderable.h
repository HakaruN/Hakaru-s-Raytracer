#pragma once
#include "Vector.h"
#include "Colour.h"
#include "Fragment.h"

#include <vector>///std vector
#include <string>
#include "Light.h"

class Renderable//abstract class for the renderable objects to inherit from
{
	public:
		virtual bool Intersects(Fragment& fragment, std::vector<Renderable*>* renderables, Light& lighting) = 0;
		virtual void SetPos(Vector pos) = 0;
		virtual void SetColour(Colour colour) = 0;

		virtual std::string GetType() = 0;
		virtual Vector GetNormal(Vector point) = 0;
		virtual Vector GetPos() = 0;
		virtual Colour GetColour() = 0;
		virtual float GetViewableArea(Vector toCamera) = 0;
		virtual void setSize(float rad) = 0;
		virtual float getSize() = 0;

	protected:
		std::string mType;
		Vector mPosition;//Sphere's position
		Colour mColour;
};