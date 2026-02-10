#include "Application.h"

Application::Application()
	: m_WindowSpec({800, 600}), m_Window(nullptr), m_Instance(VK_NULL_HANDLE)
{
}

Application::Application(uint32_t windowWidth, uint32_t windowHeight)
	: m_WindowSpec({windowWidth, windowHeight}), m_Window(nullptr), m_Instance(VK_NULL_HANDLE)
{
}

void Application::Run()
{
	InitWindow();
	InitVulkan();
	Update();
	Cleanup();
}

void Application::InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(m_WindowSpec.Width, m_WindowSpec.Height, "Vulkan", nullptr, nullptr);
}

void Application::InitVulkan()
{
	bool listAvailableExtensions = true;
	CreateInstance(listAvailableExtensions);
}

void Application::Update()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
	}
}

void Application::Cleanup()
{
	vkDestroyInstance(m_Instance, nullptr);
	
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Application::CreateInstance(bool listAvailableExtensions)
{
	/* Debugging */
	if (m_EnableValidationLayers && !CheckValidationLayerSupport()) {
		throw std::runtime_error("Validation layers requested, but not available!");
	}
	
	if (listAvailableExtensions) {
		ShowAvailableExtensions();
	}

	/* Struct setup */
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	/* Extensions */
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	/* Layers */
	if (m_EnableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
		createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}
	
	/* Attempt to create instance */
	if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create instance!");
	}

}

void Application::ShowAvailableExtensions()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
	std::cout << "available extensions:\n";
	for (const auto& extension : extensions) {
		std::cout << '\t' << extension.extensionName << '\n';
	}
}

bool Application::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : m_ValidationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}
