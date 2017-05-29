#pragma once
#ifndef SDL_CLASS_H
#define SDL_CLASS_H

#include <memory>
#include <functional>
#include "SDL/SDL.h"

class WindowManager;
class Sdl
{
    public:
        Sdl();

        ~Sdl();

        void init();

        void begin();

        void end();

        void update(std::function<void(SDL_Event&)> eventFunc);
    private:
        std::unique_ptr<WindowManager> mWindow;
        bool mShutdown;
};

#endif//SDL_CLASS_H
