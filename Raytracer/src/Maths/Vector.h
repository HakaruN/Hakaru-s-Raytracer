#pragma once
#include <math.h>


class Vector
{

	public:
		//constructors
		Vector();
		Vector(float x, float y, float z);

		//operators
		inline Vector operator + (Vector v) { return Vector(mX + v.GetX(), mY + v.GetY(), mZ + v.GetZ()); }//performs a subtraction of the vectors respective components and returns a new vector
		inline Vector operator - (Vector v) { return Vector(mX - v.GetX(), mY - v.GetY(), mZ - v.GetZ()); }//performs a subtraction of the vectors respective components and returns a new vector
		inline Vector operator * (float d ) { return Vector(mX * d, mY * d, mZ * d); }//performs a subtraction of the vectors respective components and returns a new vector
		inline Vector operator / (float d) { return Vector(mX / d, mY / d, mZ / d); }//performs a subtraction of the vectors respective components and returns a new vector

		//getterst and setters	
		inline float GetX() { return mX; }
		inline float GetY() { return mY; }
		inline float GetZ() { return mZ; }
		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);

		inline Vector cross(Vector v) {
			//float i = (mY * v.GetZ()) + (v.GetY() * mZ);
			//float j = -((mX * v.GetZ()) + (v.GetX() * mZ));
			//float k = (mX * v.GetY()) + (v.GetX() * mY);

			float i = (mY * v.GetZ()) - (v.GetY() * mZ);
			float j = -((mX * v.GetZ()) - (v.GetX() * mZ));
			float k = (mX * v.GetY()) - (v.GetX() * mY);

			return Vector(i, j, k);
		}
		inline float dot(Vector a)
		{
			return ((mX * a.GetX()) + (mY * a.GetY()) + (mZ * a.GetZ()));
		}
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
		inline double getMagnitude()
		{
			return(sqrt(
				(mX * mX) +
				(mY * mY) +
				(mZ * mZ)
			));
		}
		inline static double distanceBetweenVectors(Vector a, Vector b)
		{
			return(
				sqrt(pow(a.GetX() - b.GetX(),2))
				-
				sqrt(pow(a.GetY() - b.GetY(), 2))
				-
				sqrt(pow(a.GetZ() - b.GetZ(), 2))
				);
		}
		inline static Vector vectorBetweenVectors(Vector a, Vector b)
		{
			return a - b;
		}

	private:
		float mX, mY, mZ;
};