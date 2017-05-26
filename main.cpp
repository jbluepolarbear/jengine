#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#include "TimeClass.h"
///////////////////////////////////
#include "gl/glew.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "Input.h"
#include <crtdbg.h>
///////////////////////////////////

#pragma comment(lib, "GL/lib/glew32.lib")
#pragma comment(lib, "SDL/lib/SDL2.lib")
#pragma comment(lib, "SDL/lib/SDL2main.lib")

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//The attributes of the screen
const int SCREEN_BPP = 32;
////////////////////////////////

#include <cstdlib>
#include <iostream>

void EnableMemoryLeakChecking(int breakAlloc=-1)
{
    //Set the leak checking flag
    int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpDbgFlag);

    //If a valid break alloc provided set the breakAlloc
    if(breakAlloc!=-1) _CrtSetBreakAlloc(breakAlloc);
}

int main(int argc, char *argv[])
{
    //EnableMemoryLeakChecking();
    srand(Time::Clock());

    int width = 1280;
    int height = 720;
    std::string windowName = "Game Title";
    bool fullscreen = false;
    unsigned windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    Input input;

    input.Init();

    if (fullscreen)
    {
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    auto window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);

    SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(0);

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    bool running = true;
    Time::Timer timer;

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    float r = 0.0f, g = 0.0f, b = 0.0;
    while (running)
    {
        r = sinf(timer.GetTotal());
        g = sinf(timer.GetTotal() * 2.0f);
        b = sinf(timer.GetTotal() * 4.0f);
        timer.Start();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        input.Update();

        if (input.KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            running = false;
        }
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        timer.Stop();
    }

    input.Exit();
    SDL_Quit();

    return 0;
}