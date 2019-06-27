#include "Matrix.h"



Matrix::Matrix()
{

}

Matrix::Matrix(
	float a0, float a1, float a2, float a3,
	float b0, float b1, float b2, float b3,
	float c0, float c1, float c2, float c3,
	float d0, float d1, float d2, float d3
)
{
	ma0 = a0; ; ma1 = a1; ; ma2 = a2; ; ma3 = a3;
			  			 
	mb0 = b0; ; mb1 = b1; ; mb2 = b2; ; mb3 = b3;
			  			 
	mc0 = c0; ; mc1 = c1; ; mc2 = c2; ; mc3 = c3;

	md0 = d0; ; md1 = d1; ; md2 = d2; ; md3 = d3;
}


Matrix Matrix::Identity()
{
	return(Matrix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	));
}
Matrix Matrix::Multiply(Matrix A, Matrix B)
{
	//Top row
	float a0 = (A.GetA0() * B.GetA0()) + (A.GetA1() * B.GetB0()) + (A.GetA2() * B.GetC0()) + (A.GetA3() * B.GetD0());
	float a1 = (A.GetA0() * B.GetA1()) + (A.GetA1() * B.GetB1()) + (A.GetA2() * B.GetC1()) + (A.GetA3() * B.GetD1());
	float a2 = (A.GetA0() * B.GetA2()) + (A.GetA1() * B.GetB2()) + (A.GetA2() * B.GetC2()) + (A.GetA3() * B.GetD2());
	float a3 = (A.GetA0() * B.GetA3()) + (A.GetA1() * B.GetB3()) + (A.GetA2() * B.GetC3()) + (A.GetA3() * B.GetD3());
	//Second row
	float b0 = (A.GetB0() * B.GetA0()) + (A.GetB1() * B.GetB0()) + (A.GetB2() * B.GetC0()) + (A.GetB3() * B.GetD0());
	float b1 = (A.GetB0() * B.GetA1()) + (A.GetB1() * B.GetB1()) + (A.GetB2() * B.GetC1()) + (A.GetB3() * B.GetD1());
	float b2 = (A.GetB0() * B.GetA2()) + (A.GetB1() * B.GetB2()) + (A.GetB2() * B.GetC2()) + (A.GetB3() * B.GetD2());
	float b3 = (A.GetB0() * B.GetA3()) + (A.GetB1() * B.GetB3()) + (A.GetB2() * B.GetC3()) + (A.GetB3() * B.GetD3());
	//Third row
	float c0 = (A.GetC0() * B.GetA0()) + (A.GetC1() * B.GetB0()) + (A.GetC2() * B.GetC0()) + (A.GetC3() * B.GetD0());
	float c1 = (A.GetC0() * B.GetA1()) + (A.GetC1() * B.GetB1()) + (A.GetC2() * B.GetC1()) + (A.GetC3() * B.GetD1());
	float c2 = (A.GetC0() * B.GetA2()) + (A.GetC1() * B.GetB2()) + (A.GetC2() * B.GetC2()) + (A.GetC3() * B.GetD2());
	float c3 = (A.GetC0() * B.GetA3()) + (A.GetC1() * B.GetB3()) + (A.GetC2() * B.GetC3()) + (A.GetC3() * B.GetD3());
	//Fourth row
	float d0 = (A.GetD0() * B.GetA0()) + (A.GetD1() * B.GetB0()) + (A.GetD2() * B.GetC0()) + (A.GetD3() * B.GetD0());
	float d1 = (A.GetD0() * B.GetA1()) + (A.GetD1() * B.GetB1()) + (A.GetD2() * B.GetC1()) + (A.GetD3() * B.GetD1());
	float d2 = (A.GetD0() * B.GetA2()) + (A.GetD1() * B.GetB2()) + (A.GetD2() * B.GetC2()) + (A.GetD3() * B.GetD2());
	float d3 = (A.GetD0() * B.GetA3()) + (A.GetD1() * B.GetB3()) + (A.GetD2() * B.GetC3()) + (A.GetD3() * B.GetD3());


	return Matrix(
	a0, a1, a2, a3,
	b1, b1, b2, b3,
	c0, c1, c2, c3,
	d0, d1, d2, d3
	);
}


//setting the values in the matrix
void Matrix::SetA0(float A0) { ma0 = A0; } void Matrix::SetA1(float A1) { ma1 = A1; } void Matrix::SetA2(float A2) { ma2 = A2; } void Matrix::SetA3(float A3) { ma3 = A3; }


void Matrix::SetB0(float B0) { mb0 = B0; } void Matrix::SetB1(float B1) { mb1 = B1; } void Matrix::SetB2(float B2) { mb2 = B2; } void Matrix::SetB3(float B3) { mb3 = B3; }


void Matrix::SetC0(float C0) { mc0 = C0; } void Matrix::SetC1(float C1) { mc1 = C1; } void Matrix::SetC2(float C2) { mc2 = C2; } void Matrix::SetC3(float C3) { mc3 = C3; }


void Matrix::SetD0(float D0) { md0 = D0; } void Matrix::SetD1(float D1) { md1 = D1; } void Matrix::SetD2(float D2) { md2 = D2; } void Matrix::SetD3(float D3) { md3 = D3; }
///////////////////////////////////