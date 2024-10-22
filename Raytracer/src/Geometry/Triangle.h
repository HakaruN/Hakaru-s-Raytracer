#pragma once
#include "Maths\Vector.h"
#include "Ray.h"
#include "Colour.h"
#include "Renderable.h"
#include "Sphere.h"
class Triangle : public Renderable
{	
	public:
		Triangle(Vector position, Colour colour,Vector vert1, Vector vert2, Vector vert3);

		virtual std::string GetType() override;
		virtual Vector GetPos() override;
		virtual Colour GetColour() override;
		virtual float GetViewableArea(Vector toCamera) override;
		virtual float getSize() override;

		virtual void SetPos(Vector pos) override;
		virtual void SetColour(Colour colour) override;
		virtual inline void setSize(float rad) override;

		virtual inline bool Intersects(Fragment& fragment, std::vector<Renderable*>* renderables, Light& lighting) override;
		virtual inline Vector GetNormal(Vector point) override;

		double inline calcMaxDist();


	private:
		Colour mColour;
		Vector mOrigVertices[3];
		Vector mOrigPosition;
		Vector mVertices[3];
		Vector mPosition;
		Sphere mHitSphere;
		double maxDist;
};
