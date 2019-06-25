#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "Colour.h"
#include "Ray.h"
#include "Sphere.h"
#include "Maths.h"
#include "Triangle.h"
#include "Renderable.h"
#include "Camera.h"

class RayTracer
{		
	public:

		static void runRayTracer(int width, int height, float* frameBuffer, float* depthBuffer, Colour& background, Camera& camera, Sphere &lighting, std::vector<Renderable*>* renderables, bool isCheckerboardin, bool perspective, bool multithreaded);
		inline static void ClearPixel(float* frameBuffer, float* depthBuffer, int x, int y, int imageWidth, Colour& clearColour);
		inline static void NormalRender(float xStart, float xEnd, int yStart, int yEnd, int width, int height, float aspectRatio, bool perspective, bool checkerboarding, bool frameParity, float* frameBuffer, float* depthBuffer, Colour& background, Camera& camera, Sphere &lighting, std::vector<Renderable*>* renderables);
		inline static void Render(int bufferWidth, int widthStart, int widthEnd, int heightStart, int heightEnd, bool perspective, bool isCheckerboarding, float* frameBuffer, Colour& background, Sphere &lighting, std::vector<Renderable*>* renderables);
		inline static void CheckIntersect(Ray& ray, float& t, Sphere& lighting, Renderable* renderableObject, float* frameBuffer, float* depthBuffer, int bufferWidth, int x, int y);
		inline static Ray FireRay(Vector& pixelCoords, Vector& direction);

	private:

		Colour** frameBuffer;
		std::vector<Sphere> mSpheres;
};