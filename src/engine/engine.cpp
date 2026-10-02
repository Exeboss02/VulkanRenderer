#include "engine.h"

VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData)
{
    if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    {
        std::cout << "validation layer: " << pCallbackData->pMessage << std::endl;
    }

    return VK_FALSE;
}

void Engine::Print(std::string message)
{
    std::cout << message << std::endl;
}

bool Engine::Initialize(int windowWidth, int windowHeight)
{
    bool wSuccess = this->window.Initialize(windowWidth, windowHeight);
    bool vSuccess = this->InitializeVulkan();

    return true;
}

bool Engine::InitializeVulkan()
{
    if(!this->CreateVulkanInstance())
    {
        return false;
    }

    if(!this->CreateSurface())
    {
        return false;
    }

    return true;
}

bool Engine::CreateVulkanInstance()
{
    //Initialize volk and load vk function pointers
    if(volkInitialize() != VK_SUCCESS)
    {
        Print("volkInitialize error!");
        return false;
    }

    //Create the vulkan application instance
    //This is a good way to initialize structs with because it ensures there are no garbage data being set randomly to unassigned slots in the struct.
    //It also spares you of repeating the struct instance name before each struct slot
    VkApplicationInfo appInfo
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "VulkanRenderer",
        .apiVersion = VK_API_VERSION_1_4,
    };

    //find the required extensions for the platform and add debug for ourselves
    uint32_t instanceCount = 0;
    const char* const *extensions = SDL_Vulkan_GetInstanceExtensions(&instanceCount);
    std::vector<const char*> requestedExtensions
    {
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };

    for (int i = 0; i < instanceCount; ++i)
    {
        requestedExtensions.push_back(extensions[i]);
    };

    //we'll also need to enable the validation layer for error checking and reporting
    std::vector<const char*> requestedLayers
    {
        "VK_LAYER_KHRONOS_validation"
    };

    VkDebugUtilsMessengerCreateInfoEXT debugInfo
    {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = DebugCallback
    };

    VkInstanceCreateInfo instanceCreateInfo
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = &debugInfo,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(requestedLayers.size()),
        .ppEnabledLayerNames = requestedLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(requestedExtensions.size()),
        .ppEnabledExtensionNames = requestedExtensions.data()
    };

    if(vkCreateInstance(&instanceCreateInfo, nullptr, &this->vulkanInstance) != VK_SUCCESS)
    {
        Print("vkCreateInstance error!");
        return false;
    }

    volkLoadInstance(this->vulkanInstance);

    return true;
}

bool Engine::CreateSurface()
{
    if(!SDL_Vulkan_CreateSurface(this->window.GetSDLWindow(), this->vulkanInstance, nullptr, &this->vulkanSurface))
    {
        Print("SDL_Vulkan_CreateSurface error!");
        return false;
    }

    return true;
}

void Engine::Run()
{
}

void Engine::ShutDown()
{
    //Destroy surface
    if(this->vulkanSurface)
    {
        vkDestroySurfaceKHR(this->vulkanInstance, this->vulkanSurface, nullptr);
    }

    //Destroy instance
    if(this->vulkanInstance)
    {
        vkDestroyInstance(this->vulkanInstance, nullptr);
    }
    volkFinalize();

    //Destroy window
    this->window.ShutDown();
}
