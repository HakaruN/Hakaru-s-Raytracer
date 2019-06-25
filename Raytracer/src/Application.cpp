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
#include "Camera.h"

#include "vendor\imgui\imgui.h"
#include "vendor\imgui\imgui_impl_glfw.h"
#include "vendor\imgui\imgui_impl_opengl3.h"

#if defined (__linux__)
	#define OS_TYPE linux
#endif

#if defined (_WIN64)
	#define OS_TYPE windows64
#endif

void render(int width, int height, double fov, float* frameBuffer, float* evenBuffer, float* oddBuffer, float* depthBuffer, Colour& background, Sphere light, std::vector<Renderable*>* renderables, Camera& camera, float guiVerti, float guiHoriz,float guiDist, int guiObjectIndex, bool isCheckerboarding, bool perspective, bool multithreaded);

Colour white(255, 255, 255);
Colour darkWhite(128, 128, 128);
Colour black(0, 0, 0);
Colour red(255, 0, 0);
Colour green(0, 255, 0);
Colour blue(0, 0, 255);
Colour background(15, 15, 15);

static float hsvColour[3];
static float rgbColour[3] = { 0.7f, 0.5f, 0.7f };
static double frameRate;



int main(void)
{
	GLFWwindow* window;
	GLFWwindow* GUIWindow;

	bool isCheckerboarding = true;
	bool perspective = true;
	bool freeCam = false;
	bool multithreaded = true;
	bool show_demo_window = true;
	bool show_another_window = false;

	//background colouring
	ImVec4 clear_colour = ImVec4(0.0468f, 0.0468f, 0.0635f, 1.00f);
	rgbColour[0] = clear_colour.x;
	rgbColour[1] = clear_colour.y;
	rgbColour[2] = clear_colour.z;


	/* Initialize the library */
	if (!glfwInit())
		return -1;
	 
	const int width = 600;
	const int height = 600;

	const int GUIWidth = 500;
	const int GUIHeight = 500;
	const int colours = 4;//number of colours per pixel

	float* evenBuffer = new float[width * height * colours];
	float* oddBuffer = new float[width * height * colours];
	float* frameBuffer = new float[width * height * colours];
	float* depthBuffer = new float[width * height];


	const unsigned int n = width * height;

#pragma region OpenGL window setup
	window = glfwCreateWindow(width, height, "Render", NULL, NULL);//Creating the openGL rendering window
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//makes the rendering window the current window
	if (glewInit() != GLEW_OK)
		return -1;
	GUIWindow = glfwCreateWindow(GUIWidth, GUIHeight, "GUI", NULL, NULL);//creates the window using openGL for the GUI
	if (!GUIWindow)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(GUIWindow);//makes the GUI window the current window
	if (glewInit() != GLEW_OK)
		return -1;
	glfwMakeContextCurrent(NULL);//makes no window the current window
#pragma endregion		

#pragma region adding and renderable objects to the scene

	const int renderablesCount = 5;
	std::vector<Renderable*>* renderables = new std::vector<Renderable*>;
	renderables->reserve(renderablesCount);

	Sphere* greenSphere = new Sphere(Vector(0,0,0), green, 0.5);
	Sphere* blueSphere = new Sphere(Vector(+15, +15, 50), blue, 10);
	Sphere* redSphere = new Sphere(Vector(-15, -15, 50), red, 1);
	Sphere* whiteSphere = new Sphere(Vector(+15, -15, 50), white, 4);
	Sphere* blackSphere = new Sphere(Vector(-15, 15, 50), black, 7);

	Triangle* blueTriangle = new Triangle(Vector(0,0,0),blue,Vector(-1, 0, 50),Vector(1, +0, 50),Vector(0, +0.5, 50));

	//Triangle* blueTriangle = new Triangle(Vector(width / 2, height / 2, 50),blue,Vector(-100, 0, 10),Vector(100, 0, 10),Vector(100, 0, 10));
	
	//renderables->push_back(blueTriangle);
	renderables->push_back(greenSphere);
	renderables->push_back(blueSphere);
	//renderables->push_back(redSphere);
	//renderables->push_back(whiteSphere);
	//renderables->push_back(blackSphere);
#pragma endregion



	Vector camLook(0, 0, 100);
	Vector cameraPosition(0, 0, -1);


	Sphere light(Vector(width, height , 50), white, 40);
	bool guiOpen = true;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplGlfw_InitForOpenGL(GUIWindow, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	static float guiVerti = 0.0f;
	static float guiHoriz = 0.0f;
	static float guiSize = 0.5;
	static int guiObjectIndex = 0;
	static float lightVerti, lightHoriz = 0.25;
	static float distance = 175;
	float fov = 30;
	float t = 0; 
	Camera camera(cameraPosition, renderables->at(guiObjectIndex)->GetPos() , Vector(0,1,0), Maths::degToRad(55), width/height);

#pragma region TODO: add rendering to texture for the rendermethod instead of glDrawPixels
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
#pragma endregion

	
	float camPosX = 0;
	float camPosY = 0;
	float camPosZ = 0;
	while (!glfwWindowShouldClose(window) || !glfwWindowShouldClose(GUIWindow))
	{
		float tempFov = fov;
		light.SetPos(Vector(width * lightHoriz, height * lightVerti, 50));
		renderables->at(guiObjectIndex)->setSize(guiSize);



		glfwMakeContextCurrent(window);
		//glWindowPos2i(500, 500);
		glClear(GL_COLOR_BUFFER_BIT);
		render(width, height, fov, frameBuffer, evenBuffer, oddBuffer, depthBuffer, background, light, renderables, camera, guiVerti, guiHoriz, distance, guiObjectIndex, isCheckerboarding, perspective, multithreaded);
		glDrawPixels(width, height, GL_RGBA, GL_FLOAT, frameBuffer);	
		glfwSwapBuffers(window);

		glfwMakeContextCurrent(GUIWindow);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		///Object manipulation
		{
			//static int counter = 0;

			ImGui::Begin("Objects");                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

			ImGui::SliderFloat("Vertical", &guiVerti, -1.0f, 1.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Horisontal", &guiHoriz, -1.0f, 1.0f);

			ImGui::SliderFloat("Distance", &distance, 0.0f, 100.0f);
			ImGui::SliderFloat("Size", &guiSize, 0.0f, 100.0f);

			ImGui::SliderInt("object select", &guiObjectIndex, 0, (int)renderables->size() - 1);
				
			ImGui::ColorPicker3("Background Colour", rgbColour);
			background.SetRed(rgbColour[0]);
			background.SetGreen(rgbColour[1]);
			background.SetBlue(rgbColour[2]);
			
			//if (ImGui::Button("Button"))// Buttons return true when clicked (most widgets return true when edited/activated)
			//render(width, height, frameBuffer, evenBuffer, oddBuffer, depthBuffer, light, renderables, renderablesCount, guiVerti, guiHoriz, guiObjectIndex, isCheckerboarding);
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);
			
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		///fps counter
		{//window for fps
			ImGui::Begin("FPS");
			ImGui::Text("FPS %.2f FPS", frameRate);
			ImGui::End();
		}
		///rendering controls
		{//window for render controls
			ImGui::Begin("Render Controls");
			ImGui::Checkbox("Checkerboarding", &isCheckerboarding);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Perspective", &perspective);
			ImGui::Checkbox("Multithreading", &multithreaded);
			ImGui::End();
		}
		///camera controls
		{//window for render controls
			ImGui::Begin("Camera Controls");
			ImGui::SliderFloat("FOV", &tempFov, 5.0f, 90.0f);

			ImGui::SliderFloat("Cam-X", &camPosX, -3, 3);
			ImGui::SliderFloat("Cam-Y", &camPosY, -3, 3);
			ImGui::SliderFloat("Cam-Z", &camPosZ, -3, 150);
			ImGui::Checkbox("Free look", &freeCam);
			camLook.SetX(camPosX);
			camLook.SetY(camPosY);
			camLook.SetZ(camPosZ);
			ImGui::End();
		}
		///light controls
		{
			ImGui::Begin("Light controls");
			ImGui::SliderFloat("Light V", &lightVerti, -1.0f, 1.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Light H", &lightHoriz, -1.0f, 1.0f);
			ImGui::End();
		}

		fov = tempFov;
		if (freeCam)
		{
			cameraPosition.SetX(camPosX);
			cameraPosition.SetY(camPosY);
			cameraPosition.SetZ(camPosZ);
			camera.update(cameraPosition, Vector(0,0, cameraPosition.GetZ()+1), Vector(0, 1, 0), Maths::degToRad(fov), (float)width / (float)height);
		}
		else
		{
			//2 methods for finding the look at variable, one is the target to look at, the other is a delta vector between the looker and the lookee
			//Vector::vectorBetweenVectors(renderables->at(guiObjectIndex)->GetPos(), cameraPosition);
			//renderables->at(guiObjectIndex)->GetPos();

			camera.update(cameraPosition, Vector::vectorBetweenVectors(renderables->at(guiObjectIndex)->GetPos(), Vector(camPosX, camPosY, camPosZ)), Vector(0, 1, 0), Maths::degToRad(fov), (float)width / (float)height);
		}
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(GUIWindow);

		glfwPollEvents();		
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	//glDeleteTextures(1, &renderTexture);
	glfwTerminate();


	delete[] evenBuffer;
	delete[] oddBuffer;
	delete [] frameBuffer;
	delete [] depthBuffer;
	return 0;
}



void render(int width, int height, double fov, float* frameBuffer, float* evenBuffer, float* oddBuffer, float* depthBuffer, Colour& background, Sphere light, std::vector<Renderable*>* renderables, Camera& camera, float guiVerti, float guiHoriz, float guiDist, int guiObjectIndex, bool isCheckerboarding, bool perspective, bool multithreaded)
{
	renderables->at(guiObjectIndex)->SetPos(Vector(width * guiHoriz, height *guiVerti, guiDist));
	float t = 0;
	std::chrono::steady_clock::time_point start(std::chrono::steady_clock::now());
	RayTracer::runRayTracer(width, height, frameBuffer, evenBuffer, oddBuffer, depthBuffer, std::ref(t), background, camera, light, renderables, isCheckerboarding, perspective, multithreaded);

	std::chrono::steady_clock::time_point end(std::chrono::steady_clock::now());
	frameRate = 1 / std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}
