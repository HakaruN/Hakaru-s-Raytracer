#pragma once
#include "Maths\Vector.h"
#include "Maths\Maths.h"
#include "Colour.h"
#include <string>

class Light
{
public:
	Light(Vector pos, Colour colour);

	inline std::string getType() { return "Light"; }

	Vector getPosition();
	Colour getColour();

	void setPosition(Vector pos);
	void setColour(Colour colour);



private:
	Vector mPosition;
	Colour mColour;


};