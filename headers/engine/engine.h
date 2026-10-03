#pragma once
#include <volk/volk.h>
#include <vector>
#include "window.h"

class Engine
{
private:
    Window window;
    VkInstance vulkanInstance = nullptr;
    VkSurfaceKHR vulkanSurface = nullptr;

public:
    Engine() = default;
    ~Engine() = default;

    void Print(std::string message);

    bool Initialize(int windowWidth, int windowHeight);
    void Run();
    void ShutDown();

    bool InitializeVulkan();
    bool CreateVulkanInstance();
    bool CreateSurface();
};

//vulkan expects a function that is not part of a class or instance for this
VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );
