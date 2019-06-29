#include "Fragment.h"

Fragment::Fragment(int x, int y, Ray& ray, float& t) : mray(ray),mt(t)
{
	mx = x; my = y;
	
}

float Fragment::getT()
{
	return mt;
}

Ray& Fragment::getRay() 
{ 
	return mray; 
}

void Fragment::setT(float t)
{
	mt = t;
}