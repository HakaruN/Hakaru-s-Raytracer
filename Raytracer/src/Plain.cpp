#pragma once
#include "Plain.h"
#include "Vector.h"
#include "Maths.h"

Plain::Plain(Vector position, Colour colour, Vector vert1, Vector vert2, Vector vert3, Vector vert4)
{
	mType = "Plain";

	//sets the position
	mPosition = position;

	//sets the offset for each vertex
	mOrigVertices[0] = vert1;
	mOrigVertices[1] = vert2;
	mOrigVertices[2] = vert3;
	mOrigVertices[3] = vert4;

	//sets the absolute position for each vertex
	mVertices[0] = position + vert1;
	mVertices[1] = position + vert2;
	mVertices[2] = position + vert3;
	mVertices[3] = position + vert4;

	//sets the colour of the plane
	mColour = colour;
}
Plain::Plain()
{
	mType = "Plain";
}

std::string Plain::GetType()
{
	return mType;
}
Vector Plain::GetPos()
{
	return mPosition;
}
Colour Plain::GetColour()
{
	return mColour;
}
float Plain::GetViewableArea(Vector toCamera)
{
	return 0;
}
float Plain::getSize()
{
	return -1;
}


void Plain::SetPos(Vector position)
{
	mPosition = position;
	mVertices[0] = mPosition + mOrigVertices[0];
	mVertices[1] = mPosition + mOrigVertices[1];
	mVertices[2] = mPosition + mOrigVertices[2];
	mVertices[3] = mPosition + mOrigVertices[3];
}
void Plain::SetColour(Colour colour)
{
	mColour = colour;
}
void Plain::setSize(float rad)
{

}

bool Plain::Intersects(Fragment& fragment)
{
	float tempt = fragment.getT();
	Vector normal = (mVertices[1] - mVertices[0]).cross(mVertices[2] - mVertices[0]);
	float denom = normal.dot(fragment.getRay().GetDirection());
	if (denom > 1e-6)
	{
		Vector planeMinusOrigin = mPosition - fragment.getRay().GetOrigin();
		fragment.setT((planeMinusOrigin.dot(normal)));

		if (fragment.getT() > tempt)
			return false;
		return (fragment.getT() >= 0);
	}



	return false;
}

Vector Plain::GetNormal(Vector point)
{
	return (mVertices[1] - mVertices[0]).cross(mVertices[2] - mVertices[0]);
}