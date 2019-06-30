#include "Light.h"


Light::Light(Vector position, Colour colour)
{
	mPosition = position;
	mColour = colour;
}

Vector Light::getPosition()
{
	return mPosition;
}
Colour Light::getColour()
{
	return mColour;
}

void Light::setPosition(Vector pos)
{
	mPosition = pos;
}
void Light::setColour(Colour colour)
{
	mColour = colour;
}