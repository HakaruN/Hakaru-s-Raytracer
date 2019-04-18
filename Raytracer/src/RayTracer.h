#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include<vector>
#include "Colour.h"
#include "Ray.h"
#include "Sphere.h"
#include "Maths.h"


class RayTracer
{

public:


	static void ClearBuffer(Colour** frameBuffer, int x, int y, Colour background);
	static Ray FireRay(Vector pixelCoords, Vector direction);
	static void CheckIntersect(Ray ray, float t, Sphere lighting, Sphere targetSphere, Colour** frameBuffer, int x, int y);
	static void Render(std::ofstream &out, int widthStart, int widthEnd, int heighStart, int heightEnd,Colour** frameBuffer, float &t, Sphere &lighting, std::vector<Sphere> &spheres);
	static Sphere loadSphere(Vector pos, float size, Colour colour);
	static void runRayTracer(std::ofstream &out, int width, int height, Colour ** frameBuffer, float t, Sphere &lighting, std::vector<Sphere> &spheres);

private:

	Colour** frameBuffer;
	std::vector<Sphere> mSpheres;


};