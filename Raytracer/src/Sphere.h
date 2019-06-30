#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Colour.h"
#include "Renderable.h"
#include "Sphere.h"
class Sphere : public Renderable
{
	public:
		Sphere(Vector pos, Colour colour, float rad);
		Sphere();


		virtual inline bool Intersects(Fragment& fragment, std::vector<Renderable*>* renderables, Light& lighting) override;
		virtual inline void setSize(float rad) override;

		virtual float getSize() override;
		
		float GetRadius();
		virtual std::string GetType() override;
		virtual Vector GetNormal(Vector point) override
		{
			return (point - mPosition) / mRadius;
		}
		virtual Vector GetPos() override;
		virtual Colour GetColour() override;
		virtual float GetViewableArea(Vector toCamera) override;
		
		virtual void SetPos(Vector pos) override;
		void setRadius(float radius);
		virtual void SetColour(Colour colour) override;

	private:
		float mRadius;//Sphere's size

};