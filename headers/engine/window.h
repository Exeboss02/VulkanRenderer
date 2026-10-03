#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <iostream>

class Window
{
private:
    SDL_Window* pWindow = nullptr;
    int width = 128;
    int height = 128;

public:
    Window() = default;
    ~Window() = default;

    bool Initialize(int width, int height);
    void ShutDown();
    SDL_Window* GetSDLWindow();
};
