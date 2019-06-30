#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Colour.h"
#include "Renderable.h"
#include "Sphere.h"

class Plain : public Renderable
{
public:
	Plain(Vector pos, Colour colour, Vector point1, Vector point2, Vector point3, Vector point4);
	Plain();

	virtual std::string GetType() override;
	virtual Vector GetPos() override;
	virtual Colour GetColour() override;
	virtual float GetViewableArea(Vector toCamera) override;
	virtual float getSize() override;

	virtual void SetPos(Vector pos) override;
	virtual void SetColour(Colour colour) override;
	virtual inline void setSize(float rad) override;

	virtual inline bool Intersects(Fragment& fragment, std::vector<Renderable*>* renderables, Light& lighting) override;
	virtual Vector GetNormal(Vector point) override;



private:

	Colour mColour;
	Vector mOrigVertices[4];
	Vector mVertices[4];
	Vector mOrigPosition;
	Vector mPosition;

	
};