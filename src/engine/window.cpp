#include "window.h"

bool Window::Initialize(int width, int height)
{
    if(SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        this->pWindow = SDL_CreateWindow("Vulkan Renderer", width, height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
        this->width = width;
        this->height = height;

        if(!this->pWindow)
        {
            std::cout << "SDL_CreateWindow error!" << std::endl;
            return false;
        }

        std::cout << "sdl is working !" << std::endl;
        return true;
    }

    std::cout << "SDL_InitSubSystem error!" << std::endl;
    return false;
}

void Window::ShutDown()
{
    if(this->pWindow)
    {
        SDL_DestroyWindow(this->pWindow);
    }
    SDL_Quit();
}

SDL_Window *Window::GetSDLWindow()
{
    return this->pWindow;
}
