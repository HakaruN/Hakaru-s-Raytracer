#include <algorithm>
//#include "stdafx.h"
#include "Colour.h"

Colour::Colour(float r, float g, float b)
{
	mR = r;
	mG = g;
	mB = b;
}

Colour::Colour()
{
	mR = mG = mB = 0;
}


float Colour::GetRed()
{
	return mR;
}
float Colour::GetGreen()
{
	return mG;
}
float Colour::GetBlue()
{
	return mB;
}

void Colour::SetRed(float red)
{
	mR = red;
}
void Colour::SetGreen(float green)
{
	mG = green;
}
void Colour::SetBlue(float blue)
{
	mB = blue;
}


void Colour::clampColour()
{
	clamp__(mR);
	clamp__(mG);
	clamp__(mB);
}


