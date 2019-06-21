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
#include "Triangle.h"
#include "Renderable.h"

class RayTracer
{

public:


	inline static void ClearPixel(float* frameBuffer, float* depthBuffer, int x, int y, int imageWidth, Colour clearColour);
	static void runRayTracer(int width, int height, float* frameBuffer, float* evenBuffer, float* oddBuffer, float* depthBuffer, float &t, Sphere &lighting, std::vector<Renderable*>* renderables, bool isCheckerboardin);
	inline static void Render(int bufferWidth, int widthStart, int widthEnd, int heightStart, int heightEnd, float* frameBuffer, float* evenBuffer, float* oddBuffer, float* depthBuffer, float &t, Sphere &lighting, std::vector<Renderable*>* renderables);
	inline static Ray FireRay(Vector pixelCoords, Vector direction);
	inline static void CheckIntersect(Ray ray, float t, Sphere lighting, Renderable* renderableObject, float* frameBuffer, float* depthBuffer, int bufferWidth, int x, int y);
	

private:

	Colour** frameBuffer;
	std::vector<Sphere> mSpheres;


};