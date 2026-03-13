#pragma once

#ifdef GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>

struct WindowSpecification {
	uint32_t Width = 800;
	uint32_t Height = 600;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool IsComplete() {
		return graphicsFamily.has_value();
	}
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

	void CreateInstance(bool listAvailableExtensions = false);

	void ShowAvailableExtensions();
	std::vector<const char*> GetRequiredExtensions();
	bool CheckValidationLayerSupport();

	// Debug Messenger
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);
	void SetupDebugMessenger();
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, 
		VkDebugUtilsMessengerEXT debugMessenger, 
		const VkAllocationCallbacks* pAllocator);

	// Physical Device Selection
	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	// Logical Device Creation
	void CreateLogicalDevice();

private:
	WindowSpecification m_WindowSpec;
	GLFWwindow* m_Window;

	VkInstance m_Instance;
	VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;

	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;

	const std::vector<const char*> m_ValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

#ifdef LV_DEBUG
	const bool m_EnableValidationLayers = true;
#else
	const bool m_EnableValidationLayers = false;
#endif
};