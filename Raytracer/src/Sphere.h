#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Colour.h"
#include "Renderable.h"
class Sphere : public Renderable
{
	public:
		Sphere(Vector pos, Colour colour, float rad);
		Sphere();
		
		float GetRadius();
		void setRadius(float radius);
		virtual bool Intersects(Ray ray, float &t) override;
		virtual Vector GetNormal(Vector point) override;
		virtual Vector GetPos() override;
		virtual Colour GetColour() override;
		
		virtual void SetPos(Vector pos) override;
		virtual void SetColour(Colour colour) override;

	private:
		float mRadius;//Sphere's size

};