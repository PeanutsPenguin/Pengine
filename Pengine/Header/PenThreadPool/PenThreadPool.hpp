#pragma once 
#include "PenThreadPool/PenThreadPool.h"

namespace Pengine
{
    template<class Function, class... Args>
    auto PenThreadPool::enqueueTask(Function&& func, Args&&... args) -> std::future<std::invoke_result_t<Function, Args...>> 
    {
        using returnType = std::invoke_result_t<Function, Args...>;

        std::packaged_task<returnType()> task(std::bind(std::forward<Function>(func), std::forward<Args>(args)...));

        std::future<returnType> res = task.get_future();

        {
            std::unique_lock<std::mutex> lock(this->m_backgroundMutex);

            this->m_backgroundQueue.emplace([task = std::move(task)]() mutable { task(); });
        }

        m_condition.notify_one();
        return res;
    }

    template<class Function, class... Args>
    auto PenThreadPool::enqueueMainTask(Function&& func, Args&&... args) -> std::future<std::invoke_result_t<Function, Args...>>
    {
        using returnType = std::invoke_result_t<Function, Args...>;

        std::packaged_task<returnType()> task(std::bind(std::forward<Function>(func), std::forward<Args>(args)...));

        std::future<returnType> res = task.get_future();

        {
            std::unique_lock<std::mutex> lock(this->m_mainMutex);

            this->m_mainQueue.emplace([task = std::move(task)]() mutable { task(); });
        }

        m_condition.notify_one();
        return res;
    }
}