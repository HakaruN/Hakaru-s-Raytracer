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


	static void ClearPixel(float* frameBuffer, int x, int y, int imageWidth, Colour clearColour);
	static Ray FireRay(Vector pixelCoords, Vector direction);
	static void CheckIntersect(Ray ray, float t, Sphere lighting, Sphere targetSphere, float* frameBuffer, int bufferWidth, int x, int y);
	static Sphere loadSphere(Vector pos, float size, Colour colour);
	static void Render(std::ofstream &out, int bufferWidth, int widthStart, int widthEnd, int heighStart, int heightEnd, float* frameBuffer, float &t, Sphere &lighting, std::vector<Sphere> &spheres);
	static void runRayTracer(std::ofstream &out, int width, int height, float* cpuFrameBuffer, float t, Sphere &lighting, std::vector<Sphere> &spheres);
	

private:

	Colour** frameBuffer;
	std::vector<Sphere> mSpheres;


};