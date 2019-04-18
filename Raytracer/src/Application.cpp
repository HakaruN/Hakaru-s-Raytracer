///#pragma comment(linker, "/STACK:5000000")
#pragma comment(linker, "/HEAP:10194304")
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
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
#include "RayTracer.h"

#if defined (__linux__)
	#define OS_TYPE linux
#endif

#if defined (_WIN64)
	#define OS_TYPE windows64
#endif


Colour white(255, 255, 255);
Colour darkWhite(128, 128, 128);
Colour black(0, 0, 0);
Colour red(255, 0, 0);
Colour green(0, 255, 0);
Colour blue(0, 0, 255);

int main(void)
{


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	const int width = 1000;
	const int height = 800;
	const int colours = 5;//number of colours per pixel
	float* cpuFrameBuffer = new float[width * height * colours];
	float* depthBuffer = new float[width * height];


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "RayTracer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		return -1;



	std::vector<Sphere> spheres;
	spheres.reserve(5);
	spheres.emplace_back(Vector(width / 2, height / 2, 50), 40, blue);
	spheres.emplace_back(Vector(width - (width / 2) , height - (height / 3), 40), 80, green);
	spheres.emplace_back(Vector(width / 3, height / 4, 40), 100, red);

	spheres.emplace_back(Vector(width / 5, height / 1.5, 50), 60, white);
	spheres.emplace_back(Vector(width / 5, height / 1.5, 60), 80, black);

	Sphere lighting(Vector(400, 0, 50), 1, white);



	while (!glfwWindowShouldClose(window))
	{
		std::cout << "Rendering" << std::endl;
		auto start = std::chrono::system_clock::now();
		float t = 0;
		RayTracer::runRayTracer( width, height, cpuFrameBuffer, depthBuffer, t, lighting, spheres);

		//Stops the timer and reports how quick it was
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "Render time was: " << elapsed_seconds.count() << "s" << std::endl;


		glClear(GL_COLOR_BUFFER_BIT);

		glWindowPos2i(0, 0);
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, cpuFrameBuffer);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}



	glfwTerminate();
	delete [] cpuFrameBuffer;
	return 0;
}
