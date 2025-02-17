//#pragma comment(linker, "/STACK:5000000")
//#pragma comment(linker, "/HEAP:50000000")//reserve 50MB on the heap as the frame buffer is on the heap
//includes

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <stdlib.h>

#include "Colour.h"
#include "Ray.h"
#include "Maths\Maths.h"
#include "RayTracer.h"

#include "Geometry\Sphere.h"
#include "Geometry\Triangle.h"
#include "Geometry\Plain.h"

#include "Renderable.h"
#include "Camera.h"

#include "vendor\imgui\imgui.h"
#include "vendor\imgui\imgui_impl_glfw.h"
#include "vendor\imgui\imgui_impl_opengl3.h"

//prototyping the render function
void render(int width, int height, int coloursPerPixel, double fov, float* frameBuffer, bool renderingDepthBuffer, Colour& background, Light light, std::vector<Renderable*>* renderables, std::vector<Camera*>* cameras, int cameraIndex , float guiVerti, float guiHoriz, float guiDist, int guiObjectIndex, bool isCheckerboarding, bool perspective, bool multithreaded);

Colour white(255, 255, 255);
Colour darkWhite(128, 128, 128);
Colour black(0, 0, 0);
Colour red(255, 0, 0);
Colour green(0, 255, 0);
Colour blue(0, 0, 255);
Colour background(15, 15, 15);

static float hsvColour[3];
static float rgbBackgroundColour[3] = { 0.7f, 0.5f, 0.7f };
static float rgbObjectColour[3];
static double frameRate;

int main(void)
{


	GLFWwindow* window;
	GLFWwindow* GUIWindow;

	bool isCheckerboarding = true;
	bool perspective = true;
	bool freeCam = true;
	bool multithreaded = true;
	bool show_demo_window = true;
	bool show_another_window = false;
	bool renderingDepthBuffer = false;

	//background colouring
	ImVec4 clear_colour = ImVec4(0.0468f, 0.0468f, 0.0635f, 1.00f);
	rgbBackgroundColour[0] = clear_colour.x;
	rgbBackgroundColour[1] = clear_colour.y;
	rgbBackgroundColour[2] = clear_colour.z;


	/* Initialize the library */
	if (!glfwInit())
		return -1;

#pragma region  window and framebuffer setup


	const int width = 1920;
	const int height = 1080;

	const int GUIWidth = 500;
	const int GUIHeight = 500;

	const int coloursPerPixel = 3;//number of colours per pixel
	float* frameBuffer = new float[width * height * coloursPerPixel];
#pragma endregion

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
	const unsigned short cameraCount = 5;

	//declare the structure to store the renderable objects and cameras
	std::vector<Renderable*>* renderables = new std::vector<Renderable*>;
	std::vector<Camera*>* cameras = new std::vector<Camera*>;

	//reserve some size for the renderables and cameras
	renderables->reserve(renderablesCount);
	cameras->reserve(cameraCount);

	Sphere* greenSphere = new Sphere(Vector(1, 0.5, 35), green, 2);
	//Sphere* greenSphere = new Sphere(Vector(5, 0, 35), green, 5);
	Sphere* blueSphere = new Sphere(Vector(+20, -15, 50), blue, 10);
	Sphere* redSphere = new Sphere(Vector(+15, +15, 50), red, 1);
	Sphere* whiteSphere = new Sphere(Vector(+15, -15, 50), white, 4);
	Sphere* blackSphere = new Sphere(Vector(-15, 15, 50), black, 7);

	//starts
	for (unsigned int i = 0; i < 6; i++)
	{
		Sphere* whiteStar = new Sphere(Vector(rand() % 100 - 50, rand() % 28 + 1, 50), white, 0.25);
	}

	Triangle* blueTriangle = new Triangle(Vector(0, 0, 40), blue,Vector(-2, -2, 1),Vector(2, -2, 1),Vector(0, 2, 1));
	Triangle* greenTriangle = new Triangle(Vector(0, 15, 60), green, Vector(-4, -4, 1), Vector(4, -4, 1), Vector(0, 4, 1));

	Plain* redPlain = new Plain(Vector(0,1.22,55.12), red, Vector(-2, -2, 1), Vector(2, -2, 1), Vector(2, 2, 100), Vector(-2, 2, 100));


	//Triangle* blueTriangle = new Triangle(Vector(width / 2, height / 2, 50),blue,Vector(-100, 0, 10),Vector(100, 0, 10),Vector(100, 0, 10));
	
	//renderables->push_back(blueTriangle);

	//renderables->push_back(greenTriangle);

	renderables->push_back(greenSphere);
	renderables->push_back(blueSphere);
	renderables->push_back(redSphere);
	//renderables->push_back(whiteSphere);
	//renderables->push_back(blackSphere);

	//renderables->push_back(redPlain);




#pragma endregion

#pragma region imGUI setup
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplGlfw_InitForOpenGL(GUIWindow, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

#pragma endregion

	Vector camLook(0, 0, 100);
	Vector cameraPosition(0, 0, 0);

	Light light(Vector(width, height , 50), white);
	bool guiOpen = true;

	static int guiObjectIndex = 0;
	static int guiCameraIndex = 0;


	static float guiVerti = 0.0f;
	static float guiHoriz = 0.0f;
	static float guiSize = renderables->at(guiObjectIndex)->getSize();
	static float lightVerti, lightHoriz = 0; static float lightDepth = 50;
	static float distance = (renderables->at(guiObjectIndex)->GetPos() - cameraPosition).getMagnitude();
	float fov = 30;


	Camera* camera = new Camera(cameraPosition, renderables->at(guiObjectIndex)->GetPos(), Vector(0, 1, 0), fov, width / height);
	//cameraPosition.SetX(0.0f); cameraPosition.SetY(0.0f); cameraPosition.SetZ(0.0f);
	Camera* secondaryCamera = new Camera(cameraPosition, camLook, Vector(0, 1, 0), fov, width/height);

	cameras->push_back(camera); cameras->push_back(secondaryCamera);

#pragma region TODO: add rendering to texture for the rendermethod instead of glDrawPixels
	//texture setup for the cpu-gpu framebuffer passover
	GLuint renderTexture = 0;//handle to the texture object
	glGenTextures(1, &renderTexture);//generates a texture
	glBindTexture(GL_TEXTURE_2D, renderTexture);//binds the texture to the handle
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB	, GL_FLOAT, frameBuffer);


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
		light.setPosition(Vector(lightHoriz, lightVerti, lightDepth));
		renderables->at(guiObjectIndex)->setSize(guiSize);


		glfwMakeContextCurrent(window);
		//glWindowPos2i(500, 500);
		glClear(GL_COLOR_BUFFER_BIT);
		render(width, height, coloursPerPixel, fov, frameBuffer, renderingDepthBuffer, background, light, renderables, cameras, guiCameraIndex, guiVerti, guiHoriz, distance, guiObjectIndex, isCheckerboarding, perspective, multithreaded);

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, frameBuffer);	

		glfwSwapBuffers(window);

		glfwMakeContextCurrent(GUIWindow);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		///camera controls
		{//window for render controls
			ImGui::Begin("Camera Controls");

			ImGui::SliderInt("Camera select: ", &guiCameraIndex, 0, cameras->size() - 1);

			camPosX = cameras->at(guiCameraIndex)->mOrigin.GetX();
			camPosY = cameras->at(guiCameraIndex)->mOrigin.GetY();
			camPosZ = cameras->at(guiCameraIndex)->mOrigin.GetZ();

			tempFov = cameras->at(guiCameraIndex)->mFov;

			ImGui::SliderFloat("FOV", &tempFov, 5.0f, 90.0f);

			ImGui::SliderFloat("Cam-X", &camPosX, -5, 5);
			ImGui::SliderFloat("Cam-Y", &camPosY, -5, 5);
			ImGui::SliderFloat("Cam-Z", &camPosZ, -4, 150);
			ImGui::Checkbox("Free look", &freeCam);

			//camLook.SetX(camPosX);
			//camLook.SetY(camPosY);
			//camLook.SetZ(camPosZ);
			ImGui::End();
		}
		///Object manipulation
		{
			//static int counter = 0;

			ImGui::Begin("Objects");                          // Create a window called "Hello, world!" and append into it.

			ImGui::SliderInt("object select", &guiObjectIndex, 0, (int)renderables->size() - 1);

			guiHoriz = renderables->at(guiObjectIndex)->GetPos().GetX();
			guiVerti = renderables->at(guiObjectIndex)->GetPos().GetY();
			distance = renderables->at(guiObjectIndex)->GetPos().GetZ();
			guiSize = renderables->at(guiObjectIndex)->getSize();


			ImGui::SliderFloat("Vertical", &guiVerti, -50.0f, 50.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Horisontal", &guiHoriz, -50.0f, 50.0f);

			ImGui::SliderFloat("Distance", &distance, 0.0f, 100.0f);
			ImGui::SliderFloat("Size", &guiSize, 0.0f, 100.0f);


			
			ImGui::Text("Camera pos: %f,%f,%f", cameraPosition.GetX(), cameraPosition.GetY(), cameraPosition.GetZ());
			//ImGui::Text("Object type: %", renderables->at(guiObjectIndex)->GetType());
			ImGui::Text("Object pos: %f,%f,%f", renderables->at(guiObjectIndex)->GetPos().GetX(), renderables->at(guiObjectIndex)->GetPos().GetY(), renderables->at(guiObjectIndex)->GetPos().GetZ());
			
			//if (ImGui::Button("Button"))// Buttons return true when clicked (most widgets return true when edited/activated)
			//render(width, height, frameBuffer, evenBuffer, oddBuffer, depthBuffer, light, renderables, renderablesCount, guiVerti, guiHoriz, guiObjectIndex, isCheckerboarding);
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);
			
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		///background colour
		{
			ImGui::Begin("Background");
			ImGui::ColorPicker3("Background Colour", rgbBackgroundColour);
			background.SetRed(rgbBackgroundColour[0]);
			background.SetGreen(rgbBackgroundColour[1]);
			background.SetBlue(rgbBackgroundColour[2]);

			ImGui::End();
		}
		///object colour
		{
			ImGui::Begin("Object");

			//setting the colour picker
			rgbObjectColour[0] = renderables->at(guiObjectIndex)->GetColour().GetRed()/ 255;
			//std::cout << "Red " << renderables->at(guiObjectIndex)->GetColour().GetRed() << std::endl;
			rgbObjectColour[1] = renderables->at(guiObjectIndex)->GetColour().GetGreen() / 255;
			//std::cout << "Green " << renderables->at(guiObjectIndex)->GetColour().GetGreen() << std::endl;
			rgbObjectColour[2] = renderables->at(guiObjectIndex)->GetColour().GetBlue() / 255;
			//std::cout << "Blue " << renderables->at(guiObjectIndex)->GetColour().GetBlue() << std::endl;

			//adjust the colour picker
			ImGui::ColorPicker3("Object Colour", rgbObjectColour);

			//set the objects colour
			Colour colour(rgbObjectColour[0] * 255, rgbObjectColour[1] * 255, rgbObjectColour[2] * 255);
			//std::cout << "Red: " << rgbObjectColour[0] << "Green: " << rgbObjectColour[1] << "Blue: " << rgbObjectColour[2] << std::endl;
			renderables->at(guiObjectIndex)->SetColour(colour);

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
			ImGui::Checkbox("Render depthBuffer", &renderingDepthBuffer);
			ImGui::End();
		}
		///light controls
		{
			ImGui::Begin("Light controls");
			ImGui::SliderFloat("Light X", &lightHoriz, -80.0f, 80.0f);
			ImGui::SliderFloat("Light Y", &lightVerti, -80.0f, 80.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Light Z", &lightDepth, -80.0f, 80.0f);
			ImGui::End();
		}


		fov = tempFov;

		cameraPosition.SetX(camPosX);
		cameraPosition.SetY(camPosY);
		cameraPosition.SetZ(camPosZ);

		if (freeCam)
		{
			cameras->at(guiCameraIndex)->update(cameraPosition, Vector(0, 0, cameraPosition.GetZ() + 1), Vector(0, 1, 0), fov, (float)width / (float)height);
		}
		else
		{
			//2 methods for finding the look at variable, one is the target to look at, the other is a delta vector between the looker and the lookee
			//Vector::vectorBetweenVectors(renderables->at(guiObjectIndex)->GetPos(), cameraPosition);
			//renderables->at(guiObjectIndex)->GetPos();

			cameras->at(guiCameraIndex)->update(cameraPosition, Vector::vectorBetweenVectors(renderables->at(guiObjectIndex)->GetPos(), Vector(camPosX, camPosY, camPosZ)), Vector(0, 1, 0), fov, (float)width / (float)height);
		}
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(GUIWindow);

		glfwPollEvents();		
	}


#pragma region cleanup

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glDeleteTextures(1, &renderTexture);
	glfwTerminate();


	delete[] frameBuffer;

	delete renderables;
	delete cameras;

	delete greenSphere;
	delete blueSphere;
	delete redSphere;
	delete whiteSphere;
	delete blackSphere;

	delete blueTriangle;
	delete greenTriangle;

	delete redPlain;

	delete camera;
	delete secondaryCamera;
#pragma endregion

	return 0;
}

void render(int width, int height, int coloursPerPixel, double fov, float* frameBuffer, bool renderingDepthBuffer, Colour& background, Light light, std::vector<Renderable*>* renderables, std::vector<Camera*>* cameras, int cameraIndex, float guiVerti, float guiHoriz, float guiDist, int guiObjectIndex, bool isCheckerboarding, bool perspective, bool multithreaded)
{
	renderables->at(guiObjectIndex)->SetPos(Vector(guiHoriz, guiVerti, guiDist));
	std::chrono::steady_clock::time_point start(std::chrono::steady_clock::now());
	RayTracer::runRayTracer(width, height, coloursPerPixel, frameBuffer, renderingDepthBuffer, background, *cameras->at(cameraIndex), light, renderables, isCheckerboarding, perspective, multithreaded);

	std::chrono::steady_clock::time_point end(std::chrono::steady_clock::now());
	frameRate = 1 / std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}
