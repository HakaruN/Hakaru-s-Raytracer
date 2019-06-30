#include "Fragment.h"

Fragment::Fragment(int x, int y, Ray& ray, float& t) : mray(ray),mt(t)
{
	mx = x; my = y;
	mIsShadowed = false;
	
}

float Fragment::getT()
{
	return mt;
}

Ray& Fragment::getRay() 
{ 
	return mray; 
}

Colour Fragment::getColour()
{
	return mColour;
}

bool Fragment::getShadow()
{
	return mIsShadowed;
}

void Fragment::setT(float t)
{
	mt = t;
}

void Fragment::setColour(Colour colour)
{
	mColour = colour;
}

void Fragment::setShadow(bool shadowed)
{
	mIsShadowed = shadowed;
}