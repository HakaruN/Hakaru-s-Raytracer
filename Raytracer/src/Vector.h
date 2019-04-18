#pragma once
#include <math.h>


class Vector
{

	public:
		//constructors
		Vector();
		Vector(float x, float y, float z);

		//operators
		Vector operator + (Vector v) { return Vector(mX + v.GetX(), mY + v.GetY(), mZ + v.GetZ()); }//performs a subtraction of the vectors respective components and returns a new vector
		Vector operator - (Vector v) { return Vector(mX - v.GetX(), mY - v.GetY(), mZ - v.GetZ()); }//performs a subtraction of the vectors respective components and returns a new vector
		Vector operator * (float d ) { return Vector(mX * d, mY * d, mZ * d); }//performs a subtraction of the vectors respective components and returns a new vector
		Vector operator / (float d) { return Vector(mX / d, mY / d, mZ / d); }//performs a subtraction of the vectors respective components and returns a new vector

		//getterst and setters
		float GetX();
		float GetY();
		float GetZ();

		inline Vector Normalise()
		{
			float magnitude = (float)sqrt(
				mX * mX +
				mY * mY +
				mZ * mZ
			);
			return(Vector(
				mX / magnitude,
				mY / magnitude,
				mZ / magnitude
			));
		}

		inline float getMagnitude()
		{
			return(sqrt(
				mX * mX +
				mY * mY +
				mZ * mZ
			));
		}

	private:
		float mX, mY, mZ;
};