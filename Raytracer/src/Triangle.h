#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Colour.h"
#include "Renderable.h"
#include "Sphere.h"
class Triangle : public Renderable
{	
	public:
		Triangle(Vector position, Colour colour,Vector vert1, Vector vert2, Vector vert3);
		virtual Vector GetPos() override;
		virtual Colour GetColour() override;
		virtual float GetViewableArea(Vector toCamera) override;

		virtual void SetPos(Vector pos) override;
		virtual void SetColour(Colour colour) override;

		virtual inline bool Intersects(Ray ray, float &t) override;
		virtual Vector GetNormal(Vector point) override;

		float inline calcMaxDist();


	private:
		Colour mColour;
		Vector mOrigVertices[3];
		Vector mOrigPosition;
		Vector mVertices[3];
		Vector mPosition;
		Sphere mHitSphere;
		float maxDist;
};
