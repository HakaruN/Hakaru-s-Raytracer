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


		inline static void ClearPixel(float* frameBuffer, int x, int y, int imageWidth, Colour clearColour);
		static void runRayTracer(int width, int height, float fov, float* frameBuffer, float* evenBuffer, float* oddBuffer, float* depthBuffer, float &t, Camera& camera, Sphere &lighting, std::vector<Renderable*>* renderables, Vector ScreenPos, bool isCheckerboardin, bool perspective, bool multithreaded);
		inline static void Render(int bufferWidth, int widthStart, int widthEnd, int heightStart, int heightEnd, bool perspective, bool isCheckerboarding, float* frameBuffer, float &t, Sphere &lighting, std::vector<Renderable*>* renderables);
		inline static void NormalRender(float xStart, float xEnd, float xStride, float yStride, int width, int height, float aspectRatio, float fov, bool perspective, bool checkerboarding, bool frameParity, float* frameBuffer, float &t, Camera camera, Sphere &lighting, std::vector<Renderable*>* renderables, Vector ScreenPos);
		inline static Ray FireRay(Vector pixelCoords, Vector direction);
		inline static void CheckIntersect(Ray ray, float t, Sphere lighting, Renderable* renderableObject, float* frameBuffer, int bufferWidth, int x, int y);
	

	private:

		Colour** frameBuffer;
		std::vector<Sphere> mSpheres;


};