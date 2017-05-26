//
//  thread_pool.h
//  thread_pool
//
//  Created by Jeremy Anderson on 5/23/17.
//  Copyright © 2017 Jeremy Anderson. All rights reserved.
//

#ifndef thread_pool_h
#define thread_pool_h
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

class thread_pool
{
public:
    using Result = std::function<void()>;
    using Task = std::function<Result()>;
    thread_pool(unsigned numThreads)
        : mNumThreads(numThreads)
        , mRunning(true)
    {
        for (unsigned i = 0; i < mNumThreads; ++i)
        {
            mThreads.emplace_back(std::thread(&thread_pool::threadLoop, this));
        }
    }

    ~thread_pool()
    {
        mRunning = false;
        mConditionVariable.notify_all();
        for (auto &thread : mThreads)
        {
            thread.join();
        }
    }

    void enqueue(const Task &task)
    {
        {
            std::lock_guard<std::mutex> guard(taskMutex);
            mTasks.push(task);
        }
        mConditionVariable.notify_one();
    }

    void update()
    {
        {
            std::lock_guard<std::mutex> guard(resultMutex);
            while (!mResults.empty())
            {
                auto result = mResults.front();
                mResults.pop();
                result();
            }
        }
        std::this_thread::sleep_for(std::chrono::microseconds(0));
    }

private:
    void threadLoop()
    {
        while (mRunning)
        {
            Task task;
            {
                std::unique_lock<std::mutex> lock(taskMutex);
                mConditionVariable.wait(lock, [this]() { return !mTasks.empty() || !mRunning; });
                if (!mRunning)
                {
                    break;
                }
                task = mTasks.front();
                mTasks.pop();
            }
            if (task != nullptr)
            {
                auto result = task();
                {
                    std::lock_guard<std::mutex> guard(resultMutex);
                    mResults.push(result);
                }
            }
        }
    }

    std::mutex taskMutex;
    std::queue<Task> mTasks;
    std::mutex resultMutex;
    std::queue<Result> mResults;
    std::atomic<bool> mRunning;
    std::vector<std::thread> mThreads;
    std::condition_variable mConditionVariable;

    const unsigned mNumThreads;
};


#endif /* thread_pool_h */
