#pragma once

class Matrix
{
public:
	Matrix();
	Matrix(
		float a0, float a1, float a2, float a3,
		float b0, float b1, float b2, float b3,
		float c0, float c1, float c2, float c3,
		float d0, float d1, float d2, float d3
		);
	
	static Matrix Identity();

	static Matrix Multiply(Matrix A, Matrix B);


	//getting the values in the matrix
	inline float GetA0() { return ma0; } inline float GetA1() { return ma1; } inline float GetA2() { return ma2; } inline float GetA3() { return ma3; }


	inline float GetB0() { return mb0; } inline float GetB1() { return mb1; } inline float GetB2() { return mb2; } inline float GetB3() { return mb3; }


	inline float GetC0() { return mc0; } inline float GetC1() { return mc1; } inline float GetC2() { return mc2; } inline float GetC3() { return mc3; }


	inline float GetD0() { return md0; } inline float GetD1() { return md1; } inline float GetD2() { return md2; } inline float GetD3() { return md3; }
	//////////////////////////////////




	void SetA0(float A0); void SetA1(float A1); void SetA2(float A2); void SetA3(float A3);
	void SetB0(float B0); void SetB1(float B1); void SetB2(float B2); void SetB3(float B3);
	void SetC0(float C0); void SetC1(float C1); void SetC2(float C2); void SetC3(float C3);
	void SetD0(float D0); void SetD1(float D1); void SetD2(float D2); void SetD3(float D3);



private:
	float ma0, ma1, ma2, ma3;
	float mb0, mb1, mb2, mb3;
	float mc0, mc1, mc2, mc3;
	float md0, md1, md2, md3;
};