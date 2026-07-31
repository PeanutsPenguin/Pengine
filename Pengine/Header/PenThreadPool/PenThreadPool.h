#pragma once 

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <type_traits>

namespace Pengine
{
	class PenThreadPool
	{
	public:
		PenThreadPool();
		PenThreadPool(const PenThreadPool& other) = delete;
		PenThreadPool(PenThreadPool&& other) = delete;
		~PenThreadPool();

		PenThreadPool& operator=(const PenThreadPool& rhs) = delete;
		PenThreadPool& operator=(PenThreadPool&& rhs) = delete;

		template<class Function, class... Args>
		auto enqueueTask(Function&& f, Args&&... args) -> std::future<std::invoke_result_t<Function, Args...>>;

		template<class Function, class... Args>
		auto enqueueMainTask(Function&& f, Args&&... args) -> std::future<std::invoke_result_t<Function, Args...>>;

		void executeMainTask();

	private:
		std::queue<std::move_only_function<void()>> m_backgroundQueue;		//<-Queue for tasks that can be executed anywhere
		std::mutex m_backgroundMutex;										//<-Mutex to avoid mutliple call on the queue at the same time

		std::queue<std::move_only_function<void()>> m_mainQueue;			//<-Queue for tasks that can be executed only on the main thread
		std::mutex m_mainMutex;												//<-Mutex to avoid mutliple call on the main queue at the same time

		std::condition_variable_any m_condition;							//<-Awake condition for the threads
		std::vector<std::jthread> m_workers;								//<-Vector of threads
	};
}
#include "PenThreadPool.hpp"