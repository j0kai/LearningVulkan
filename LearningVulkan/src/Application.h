#pragma once

#ifdef GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <stdexcept>
#include <cstdlib>

struct WindowSpecification {
	uint32_t Width = 800;
	uint32_t Height = 600;
};

class Application
{
public:
	Application();
	Application(uint32_t windowWidth, uint32_t windowHeight);

	void Run();

private:
	void InitWindow();
	void InitVulkan();
	void Update();
	void Cleanup();

	void CreateInstance();
private:
	WindowSpecification m_WindowSpec;
	GLFWwindow* m_Window;

	VkInstance m_Instance;
};