#include "thread_pool.h"

#ifndef JENGINE_H
#define JENGINE_H

class WindowManager;
class JEngine
{
    public:
        JEngine();
        ~JEngine();
        void Initialize();
        void Run();
        thread_pool &ThreadPool();
    private:
        thread_pool mThreadPool;
        std::shared_ptr<WindowManager> mWindow;
};

#endif//JENGINE_H