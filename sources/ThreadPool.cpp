/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ThreadPool
*/

#include <Thread/ThreadPool.hpp>

namespace Plazza
{
    ThreadPool::ThreadPool(const uint& threadCount, const FoodStock* stock)
    {
        this->_threadCount = threadCount;
        this->_stock = const_cast<FoodStock*>(stock);
        this->_threads.reserve(threadCount);
        this->_done = false;
    }

    ThreadPool::~ThreadPool()
    {
        this->_done = true;

        this->_cv.notify_all(); // Unlock all threads
        this->WaitAll();
        this->_threads.clear();
    }

    void ThreadPool::StartAll()
    {
        for (uint i = 0; i < this->_threadCount; i += 1)
            this->_threads.emplace_back(Thread());
    }

    void ThreadPool::WaitAll()
    {
        for (auto &thread : this->_threads)
            thread.Wait();
    }

    void ThreadPool::AddTask(const Pizza& order)
    {
        std::lock_guard<std::mutex> lk(this->_mutex);

        this->_tasks.Push(order);
        this->_cv.notify_one();
    }

    SafeQueue<Pizza>& ThreadPool::GetTasksDone()
    {
        std::lock_guard<std::mutex> lk(this->_mutex);

        return this->_tasksDone;
    }

    SafeQueue<Pizza>& ThreadPool::GetPendingTasks()
    {
        std::lock_guard<std::mutex> lk(this->_mutex);

        return this->_tasks;
    }

    const uint ThreadPool::TasksCount()
    {
        std::lock_guard<std::mutex> lk(this->_mutex);

        return static_cast<uint>(this->_tasks.Size());
    }

    void ThreadPool::ExecuteTasks()
    {
        for (auto& thread : this->_threads)
            thread.Run(&ThreadPool::RunTask, this, &thread);
    }

    void ThreadPool::RunTask(Thread* thread)
    {
        bool cook = true;

        while (!_done) {
            Pizza pizza;
            cook = true;

            // @Important: Create a scope, so we don't lock the queue for longer than necessary
            {
                std::unique_lock<std::mutex> u_lock(_mutex);

                _cv.wait(u_lock, [&] {
                    return !_tasks.IsEmpty() || _done;
                });

                if (_done)
                    return;

                thread->SetActive(true);
                pizza = _tasks.Pop();

                // @Info: Remove Ingredients from stock and check if we can cook
                for (auto& ig : pizza.getIngredients()) {
                    if (!this->_stock->getIngredient(ig)) {
                        this->_tasks.Push(pizza);
                        cook = false;
                        break;
                    }
                }
            }

            if (cook) {
                bool cooked = Cook::CookPizza(pizza, &_done);

                if (cooked) {
                    std::unique_lock<std::mutex> u_lock(this->_mutex);
                    this->_tasksDone.Push(pizza);
                }
            }

            thread->SetActive(false);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
