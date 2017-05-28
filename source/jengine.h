#ifndef JENGINE_H
#define JENGINE_H

#include "thread_pool.h"

class JTextureManager;

class WindowManager;
class JEngine
{
    public:
        JEngine();
        ~JEngine();
        void Initialize();
        void Run();
        thread_pool &ThreadPool();
        const std::string ResourcesPath() const;
    private:
        std::shared_ptr<thread_pool> mThreadPool;
        std::shared_ptr<WindowManager> mWindow;
        std::string mResourcesPath;
        std::shared_ptr<JTextureManager> mTextureManager;
};

#endif//JENGINE_H