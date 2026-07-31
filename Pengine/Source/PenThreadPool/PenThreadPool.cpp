#include "PenThreadPool/PenThreadPool.h"

namespace Pengine
{
	PenThreadPool::PenThreadPool()
	{
        size_t threads = std::thread::hardware_concurrency() - 1;

        for (size_t i = 0; i < threads; ++i) 
        {
            this->m_workers.emplace_back
            (
                [this](std::stop_token stoken) 
                {
                    while (!stoken.stop_requested()) 
                    {
                        std::move_only_function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->m_backgroundMutex);

                            // Wait until there is a task or a stop is requested
                            this->m_condition.wait(lock, stoken, [this, &stoken] {return !this->m_backgroundQueue.empty() || stoken.stop_requested(); });

                            if (stoken.stop_requested() && this->m_backgroundQueue.empty())
                                return;

                            task = std::move(this->m_backgroundQueue.front());
                            this->m_backgroundQueue.pop();
                        }

                        task();
                    }
                }
            );
        }
	}

    PenThreadPool::~PenThreadPool()
    {
        for (auto& worker : this->m_workers) 
        {
            worker.request_stop();
        }

        this->m_condition.notify_all();

        this->m_workers.clear();
    }

    void PenThreadPool::executeMainTask()
    {
        std::queue<std::move_only_function<void()>> tasks_to_execute;

        {
            std::unique_lock<std::mutex> lock(this->m_mainMutex);
            tasks_to_execute.swap(this->m_mainQueue);
        }

        while (!tasks_to_execute.empty()) 
        {
            tasks_to_execute.front()();
            tasks_to_execute.pop();
        }
    }
}