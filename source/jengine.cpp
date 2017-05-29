#include "jengine.h"
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#include "TimeClass.h"
#include "gl/glew.h"
#include "sdl_class.h"
///////////////////////////////////
#include "Input.h"
#include <crtdbg.h>
#include "Utilities.h"
#include "JTextureManager.h"
#include "JTexture.h"
#include "Shader.h"
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

JEngine::JEngine()
{
    mThreadPool = std::make_shared<thread_pool>(10);
    mSdl = std::make_unique<Sdl>();
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
    mSdl->init();
    int glerror = glGetError();
    mTextureManager = std::make_shared<JTextureManager>(*this);
    glerror = glGetError();
    srand((int)Time::Clock());
}

void JEngine::Run()
{
    Input input;

    input.Init();
    Shader shader;
    shader.AddFragmentShader(ResourcesPath() + "shaders/frame.fs");
    shader.AddVertexShader(ResourcesPath() + "shaders/frame.vs");
    shader.LinkProgram();
    int glerror = glGetError();

    bool running = true;
    Time::Timer timer;
    auto jTexture = mTextureManager->GetTexture("textures\\killer bunny.png");
    float r = 0.0f, g = 0.0f, b = 0.0;
    while (running)
    {
        mSdl->update([&running](SDL_Event &event)
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        });
        timer.Start();

        input.Update();

        if (input.KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            running = false;
        }
        ThreadPool().update();

        if (!running)
        {
            break;
        }

        mSdl->begin();
        glerror = glGetError();
        shader.BindProgram();
        glerror = glGetError();
        glBindTexture(GL_TEXTURE_2D, jTexture->GetTextureId());
        shader.uniform("Texture", 0);
        shader.uniform("alpha", 1.0f);
        float colors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        shader.uniform<3>("Color", colors);
        glerror = glGetError();
        // Draw the texture on a quad, using u3 and v3 to correct non power of two texture size.
        glBegin(GL_QUADS);
        glerror = glGetError();
        glTexCoord2d(0, 0); glVertex2f(0, 0);
        glTexCoord2d(1.0, 0); glVertex2f((double)jTexture->GetWidth(), 0);
        glTexCoord2d(1.0, 1.0); glVertex2f((double)jTexture->GetWidth(), (double)jTexture->GetHeight());
        glTexCoord2d(0, 1.0); glVertex2f(0, (double)jTexture->GetHeight());
        glEnd();
        glerror = glGetError();
        mSdl->end();
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
