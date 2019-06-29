#pragma once
#include "Ray.h"
#include "Vector.h"
#include "Maths.h"


class Fragment
{
public:
	Fragment(int x, int y, Ray& ray, float& t);

	float getT();
	Ray& getRay();

	void setT(float t);


private:
	int mx, my;
	Ray& mray;
	float& mt;

};