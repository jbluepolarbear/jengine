#include "sdl_class.h"

#include "gl/glew.h"
#include "SDL/SDL_opengl.h"
#include <string>

////////////////////////////////
#pragma comment(lib, "GL/lib/glew32.lib")
#pragma comment(lib, "SDL/lib/SDL2.lib")
#pragma comment(lib, "SDL/lib/SDL2main.lib")

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
////////////////////////////////


class WindowManager
{
public:
    std::string mWindowName;
    unsigned mWidth;
    unsigned mHeight;
    unsigned mWindowFlags;
    SDL_Window *mWindow;
};

Sdl::Sdl()
{
    mWindow = std::make_unique<WindowManager>();
    mWindow->mWidth = 1280;
    mWindow->mHeight = 720;
    mWindow->mWindowName = "Game Title";
    bool fullscreen = false;
    mWindow->mWindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    if (fullscreen)
    {
        mWindow->mWindowFlags |= SDL_WINDOW_FULLSCREEN;
    }
}

Sdl::~Sdl()
{
    // Terminate SDL
    SDL_Quit();
}

void Sdl::init()
{
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


    // Set OpenGL viewport and states
    glViewport(0, 0, mWindow->mWidth, mWindow->mHeight);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Sdl::begin()
{
    // Clear screen
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Sdl::end()
{
    // Present frame buffer
    SDL_GL_SwapWindow(mWindow->mWindow);
}

void Sdl::update(std::function<void(SDL_Event &)> eventFunc)
{
    SDL_Event event;
    // Process incoming events
    while(SDL_PollEvent(&event)) 
    {
        eventFunc(event);
        switch(event.type)
        {
            case SDL_WINDOWEVENT_RESIZED:   // Window size has changed
                // Resize SDL video mode
                mWindow->mWidth = event.window.data1;
                mWindow->mHeight = event.window.data1;
                SDL_SetWindowSize(mWindow->mWindow, mWindow->mWidth, mWindow->mHeight);

                // Resize OpenGL viewport
                glViewport(0, 0, mWindow->mWidth, mWindow->mHeight);

                // Restore OpenGL states (SDL seems to lost them)
                glEnable(GL_DEPTH_TEST);
                glDisable(GL_CULL_FACE);

                break;
        }
    }
}
