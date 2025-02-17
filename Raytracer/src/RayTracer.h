#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "Colour.h"
#include "Ray.h"
#include "Geometry\Sphere.h"
#include "Maths\Maths.h"
#include "Geometry\Triangle.h"
#include "Renderable.h"
#include "Camera.h"

class RayTracer
{		
	public:

		static void runRayTracer(int width, int height, int coloursPerPixel, float* frameBuffer, bool depthRender, Colour& background, Camera& camera, Light &lighting, std::vector<Renderable*>* renderables, bool isCheckerboardin, bool perspective, bool multithreaded);
		inline static void ClearPixel(float* frameBuffer, int x, int y, int imageWidth, int coloursPerPixel, Colour& clearColour);
		inline static void CheckIntersect(Ray& ray, float& t, Light& lighting, std::vector<Renderable*>* renderables, int renderableIndex, int coloursPerPixel, float* frameBuffer, bool depthRender, int bufferWidth, int x, int y);
		inline static void Render(int xStart, int xEnd, int yStart, int yEnd, int width, int height, int coloursPerPixel, float aspectRatio, bool perspective, bool checkerboarding, bool frameParity, float* frameBuffer, bool depthRenderr, Colour& background, Camera& camera, Light &lighting, std::vector<Renderable*>* renderables);
		inline static Ray FireRay(Vector& pixelCoords, Vector& direction);

	private:

		Colour** frameBuffer;
		std::vector<Sphere> mSpheres;
};