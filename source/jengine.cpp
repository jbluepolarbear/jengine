#include "jengine.h"
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#include "TimeClass.h"
///////////////////////////////////
#include "gl/glew.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "Input.h"
#include <crtdbg.h>
#include "Utilities.h"
#include "JTextureManager.h"
///////////////////////////////////

#pragma comment(lib, "GL/lib/glew32.lib")
#pragma comment(lib, "SDL/lib/SDL2.lib")
#pragma comment(lib, "SDL/lib/SDL2main.lib")

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
////////////////////////////////

#include <cstdlib>
#include <iostream>

void EnableMemoryLeakChecking(int breakAlloc = -1)
{
    //Set the leak checking flag
    int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpDbgFlag);

    //If a valid break alloc provided set the breakAlloc
    if (breakAlloc != -1) _CrtSetBreakAlloc(breakAlloc);
}

class WindowManager
{
public:
    std::string mWindowName;
    unsigned mWidth;
    unsigned mHeight;
    unsigned mWindowFlags;
    SDL_Window *mWindow;
};

JEngine::JEngine()
{
    mThreadPool = std::make_shared<thread_pool>(10);
    mTextureManager = std::make_shared<JTextureManager>(*this);
}

JEngine::~JEngine()
{
    SDL_Quit();
}

auto replace(const std::string &str, const std::string &token, const std::string &replaceToken)
{
    std::string rStr = str;
    while (true)
    {
        auto found = rStr.find_first_of(token);
        if (found == std::string::npos)
        {
            break;
        }

        rStr = rStr.replace(found, token.size(), replaceToken);
    }

    return rStr;
}

void JEngine::Initialize()
{
    EnableMemoryLeakChecking();
    mResourcesPath = GetProgramPath() + "\\resources\\";
    //mResourcesPath = replace(mResourcesPath, "\\", "/");
    mTextureManager->GetTexture("texture\\killer bunny.png");
    srand((int)Time::Clock());
    mWindow = std::make_shared<WindowManager>();
    mWindow->mWidth = 1280;
    mWindow->mHeight = 720;
    mWindow->mWindowName = "Game Title";
    bool fullscreen = false;
    mWindow->mWindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    if (fullscreen)
    {
        mWindow->mWindowFlags |= SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    mWindow->mWindow = SDL_CreateWindow(mWindow->mWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindow->mWidth, mWindow->mHeight, mWindow->mWindowFlags);

    SDL_GL_CreateContext(mWindow->mWindow);
    SDL_GL_SetSwapInterval(0);

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
}

void JEngine::Run()
{
    Input input;

    input.Init();

    bool running = true;
    Time::Timer timer;

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    float r = 0.0f, g = 0.0f, b = 0.0;
    while (running)
    {
        ThreadPool().update();
        r = (float)sin(timer.GetTotal());
        g = (float)sin(timer.GetTotal() * 2.0);
        b = (float)sin(timer.GetTotal() * 4.0);
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

        SDL_GL_SwapWindow(mWindow->mWindow);
        timer.Stop();
    }

    input.Exit();
}

thread_pool &JEngine::ThreadPool()
{
    return *mThreadPool;
}

const std::string JEngine::ResourcesPath() const
{
    return mResourcesPath;
}
