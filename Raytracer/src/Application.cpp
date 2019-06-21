//#pragma comment(linker, "/STACK:5000000")
#pragma comment(linker, "/HEAP:10000000")//reserve 10MB on the heap as the frame buffer is on the heap
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
#include "Triangle.h"
#include "Renderable.h"

#include "vendor\imgui\imgui.h"
#include "vendor\imgui\imgui_impl_glfw.h"
#include "vendor\imgui\imgui_impl_opengl3.h"

#if defined (__linux__)
	#define OS_TYPE linux
#endif

#if defined (_WIN64)
	#define OS_TYPE windows64
#endif

void render(int width, int height, float* frameBuffer, float* evenBuffer, float* oddBuffer, float* depthBuffer, Sphere light, std::vector<Renderable*>* renderables, float guiVerti, float guiHoriz,float guiDist, int guiObjectIndex, bool isCheckerboarding);

Colour white(255, 255, 255);
Colour darkWhite(128, 128, 128);
Colour black(0, 0, 0);
Colour red(255, 0, 0);
Colour green(0, 255, 0);
Colour blue(0, 0, 255);

static double frameRate;
static bool sphericalHitDetection = false;



int main(void)
{
	GLFWwindow* window;

	bool isCheckerboarding = false;
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	const int width = 920;
	const int height = 310;
	const int colours = 4;//number of colours per pixel

	float* evenBuffer = new float[width * height * colours];
	float* oddBuffer = new float[width * height * colours];
	float* frameBuffer = new float[width * height * colours];
	float* depthBuffer = new float[width * height];
	//float* stexil = new float[width * height];


	Vector cameraPos(0,0,0);
	


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


		
	const int renderablesCount = 5;
	std::vector<Renderable*>* renderables = new std::vector<Renderable*>;
	renderables->reserve(renderablesCount);

	Sphere* greenSphere = new Sphere(Vector(0, 0, 40), green, 40);
	Sphere* blueSphere = new Sphere(Vector(200, +200, 50), blue, 40);
	Sphere* redSphere = new Sphere(Vector(width / 4, height / 2, -50), red, 50);
	//Sphere* whiteSphere = new Sphere(Vector(width / 2, height / 2, 50), white, 60);
	//Sphere* blackSphere = new Sphere(Vector(width / 2, height / 2, 50), black, 80);

	Triangle* blueTriangle = new Triangle(Vector(width / 2, height / 2, 50),blue,Vector(100, +100, 50),Vector(300, +150, 50),Vector(200, +200, 50));

	//wrong
	//Triangle* blueTriangle = new Triangle(Vector(width / 2, height / 2, 50),blue,Vector(-100, 0, 10),Vector(100, 0, 10),Vector(100, 0, 10));
	
	//renderables->push_back(blueTriangle);
	renderables->push_back(greenSphere);
	//renderables->push_back(blueSphere);
	//renderables->push_back(redSphere);


	Vector cameraPosition(0, 0, 0);
	Sphere light(Vector(width, height , 50), white, 40);


	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	static float hsvColour[3];
	static float rgbColour[3];

	static float guiVerti = 0.5f;
	static float guiHoriz = 0.5f;
	static float guiSize = 50;
	static int guiObjectIndex = 0;
	static float lightVerti, lightHoriz = 0.25;
	static float distance = 40;
	static float fov = 80;
	
	float t = 0;

	//texture setup for the cpu-gpu framebuffer passover
	GLuint renderTexture = 0;//handle to the texture object
	glGenTextures(1, &renderTexture);//generates a texture
	glBindTexture(GL_TEXTURE_2D, renderTexture);//binds the texture to the handle
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, frameBuffer);

	
	//preps the render for the incoming texture 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTexture);

	while (!glfwWindowShouldClose(window))
	{



		render(width, height, frameBuffer, evenBuffer, oddBuffer, depthBuffer, light, renderables, guiVerti, guiHoriz, distance, guiObjectIndex, isCheckerboarding);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(width, height, GL_RGBA, GL_FLOAT, frameBuffer);
		//spheres[guiSphereIndex].SetColour(Colour(rgbColour[0], rgbColour[1], rgbColour[2]));
		light.SetPos(Vector(width * lightHoriz, height * lightVerti, 50 ));		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glWindowPos2i(0, 0);


		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			//static int counter = 0;

			ImGui::Begin("Blue balls");                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Checkerboarding", &isCheckerboarding);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);
			ImGui::SliderFloat("FOV", &fov, 0.0f, 90.0f);

			ImGui::SliderFloat("Vertical", &guiVerti, -1.0f, 1.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Horisontal", &guiHoriz, -1.0f, 1.0f);
			ImGui::SliderFloat("Depth", &distance, 0.0f, 400.0f);
			//ImGui::SliderFloat("Size", &guiSize, 0.0f, 100.0f);

			ImGui::SliderFloat("Lighting Vertical", &lightVerti, 0.0f, 1.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Lighting Horizontal", &lightHoriz, 0.0f, 1.0f);
			ImGui::SliderInt("object select", &guiObjectIndex, 0, renderables->size() - 1);
			//ImGui::ColorEdit3("clear color", hsvColour);//Edit 3 floats representing a color
			//ImGui::ColorConvertHSVtoRGB(hsvColour[0], hsvColour[1], hsvColour[2], rgbColour[0], rgbColour[1], rgbColour[2]);

			
			//if (ImGui::Button("Button"))// Buttons return true when clicked (most widgets return true when edited/activated)
			//render(width, height, frameBuffer, evenBuffer, oddBuffer, depthBuffer, light, renderables, renderablesCount, guiVerti, guiHoriz, guiObjectIndex, isCheckerboarding);
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);
			
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("FPS %.2f FPS", frameRate);
			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);

		glfwPollEvents();
		
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glDeleteTextures(1, &renderTexture);

	glfwTerminate();

	delete[] evenBuffer;
	delete[] oddBuffer;
	delete [] frameBuffer;
	delete [] depthBuffer;
	return 0;
}



void render(int width, int height, float* frameBuffer, float* evenBuffer, float* oddBuffer, float* depthBuffer, Sphere light, std::vector<Renderable*>* renderables, float guiVerti, float guiHoriz, float guiDist, int guiObjectIndex, bool isCheckerboarding)
{
	renderables->at(guiObjectIndex)->SetPos(Vector(width * guiHoriz, height *guiVerti, guiDist));
	float t = 0;
	std::chrono::steady_clock::time_point start(std::chrono::steady_clock::now());
	RayTracer::runRayTracer(width, height, frameBuffer, evenBuffer, oddBuffer, depthBuffer, std::ref(t), light, renderables, isCheckerboarding);

	std::chrono::steady_clock::time_point end(std::chrono::steady_clock::now());
	frameRate = 1 / std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}
