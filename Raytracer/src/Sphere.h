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


		virtual inline bool Intersects(Ray ray, float &t) override;
		virtual inline void setSize(float rad) override;

		
		float GetRadius();
		virtual Vector GetNormal(Vector point) override;
		virtual Vector GetPos() override;
		virtual Colour GetColour() override;
		virtual float GetViewableArea(Vector toCamera) override;
		
		virtual void SetPos(Vector pos) override;
		void setRadius(float radius);
		virtual void SetColour(Colour colour) override;

	private:
		float mRadius;//Sphere's size

};