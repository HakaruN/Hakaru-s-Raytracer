#pragma once
class Colour
{
public:
	Colour();
	Colour(float r, float g, float b);

	Colour operator + (Colour  c) { return Colour((mR + c.GetRed())/2, (mG + c.GetGreen())/2, (mB + c.GetBlue())/2); }
	Colour operator * (float  f) { return Colour(mR * f, mG * f, mB * f); }
	Colour operator / (float  f) { return Colour(mR / f, mG / f, mB / f); }

	float GetRed();
	float GetGreen();
	float GetBlue();


	void SetRed(float red);
	void SetGreen(float green);
	void SetBlue(float blue);

	void clampColour();



private:
	float mR, mG, mB;


	static void clamp__(float &a) {
		if (a < 0x00) {
			a = 0x00;
		}
		else if (a > 0xff) {
			a = 0xff;
		}
	}
};
