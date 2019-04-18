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


#include "vendor\imgui\imgui.h"
#include "vendor\imgui\imgui_impl_glfw.h"
#include "vendor\imgui\imgui_impl_opengl3.h"

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

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	const int width = 600;
	const int height = 600;
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
	spheres.emplace_back(Vector(width / 2, height / 2, 50), 80, green);
	spheres.emplace_back(Vector(width / 2, height / 2, 50), 100, red);
	//spheres.emplace_back(Vector(width / 2, height / 2, 50), 60, white);
	//spheres.emplace_back(Vector(width / 2, height / 2, 50), 80, black);


	Vector cameraPosition(0, 0, 0);
	Sphere lighting(Vector(width / 2, height / 2, 50), 1, white);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	static float guiVerti = 0.5f;
	static float guiHoriz = 0.5f;
	static float guiSize = 50;
	static int guiSphereIndex = 0;

	static float lightVerti, lightHoriz = 0.25;

	while (!glfwWindowShouldClose(window))
	{
		std::cout << "Rendering" << std::endl;
		auto start = std::chrono::system_clock::now();
		float t = 0;
		RayTracer::runRayTracer( width, height, cpuFrameBuffer, depthBuffer, t, lighting, spheres);
		spheres[guiSphereIndex].SetPos(Vector( width * guiHoriz, height *guiVerti,0));
		spheres[guiSphereIndex].setRadius(guiSize);
		lighting.SetPos(Vector(width * lightHoriz, height * lightVerti, 50 ));

		//Stops the timer and reports how quick it was
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "Render time was: " << elapsed_seconds.count() << "s" << std::endl;




		glClear(GL_COLOR_BUFFER_BIT);
		//ImGui_ImplGlfw_NewFrame();	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glWindowPos2i(0, 0);
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, cpuFrameBuffer);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			
			static int counter = 0;

			ImGui::Begin("Blue balls");                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("Vertical Pos", &guiVerti, 0.0f, 1.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Horisontal Pos", &guiHoriz, 0.0f, 1.0f);
			ImGui::SliderFloat("Size", &guiSize, 0.0f, 100.0f);
			ImGui::SliderInt("Sphere selector",&guiSphereIndex, 0, spheres.size()-1);

			ImGui::SliderFloat("Lighting Vertical Pos", &lightVerti, 0.0f, 1.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Lighting Horisontal Pos", &lightHoriz, 0.0f, 1.0f);
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			/*
			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);
			*/
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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

	glfwTerminate();
	delete [] cpuFrameBuffer;
	return 0;
}
