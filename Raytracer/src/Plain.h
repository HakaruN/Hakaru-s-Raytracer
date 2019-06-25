#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Colour.h"
#include "Renderable.h"

class Plain : public Renderable
{
public:
	Plain(Vector pos, Colour colour, Vector point1, Vector point2, Vector point3, Vector point4);
	Plain();

	virtual inline bool Intersects(Ray ray, float &t) override;

private:


};