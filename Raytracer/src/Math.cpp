#pragma once
//#include "stdafx.h"
#include "Maths.h"

float Maths::dot(Vector a, Vector b) {return (a.GetX() * b.GetX()) + (a.GetY() * b.GetY()) + (a.GetZ() * b.GetZ());}