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


	inline static void ClearPixel(float* frameBuffer,float* depthBuffer, int x, int y, int imageWidth, Colour clearColour);
	inline static void Render(int bufferWidth, int widthStart, int widthEnd, int heighStart, int heightEnd, float* frameBuffer, float* depthBuffer, float &t, Sphere &lighting, std::vector<Sphere> &spheres);
	inline static Ray FireRay(Vector pixelCoords, Vector direction);
	inline static void CheckIntersect(Ray ray, float t, Sphere lighting, Sphere targetSphere, float* frameBuffer, float* depthBuffer, int bufferWidth, int x, int y);
	static Sphere loadSphere(Vector pos, float size, Colour colour);
	static void runRayTracer(int width, int height, float* cpuFrameBuffer, float* depthBuffer, float t, Sphere &lighting, std::vector<Sphere> &spheres);
	

private:

	Colour** frameBuffer;
	std::vector<Sphere> mSpheres;


};