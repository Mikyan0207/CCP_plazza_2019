/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ThreadPool
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <fstream>
#include <sstream>
#include <vector>

#include <Cook.hpp>
#include <FoodStock.hpp>
#include <SafeQueue/SafeQueue.hpp>
#include <Thread/Thread.hpp>

namespace Plazza
{
    class ThreadPool
    {
        public:
            ThreadPool(const uint& cooksNb, const FoodStock* foodStock);
            ~ThreadPool();

        public:
            void StartAll();
            void WaitAll();
            void AddTask(const Plazza::Pizza& order);
            void ExecuteTasks();
            inline const uint& Size() const { return this->_threadCount; }
            inline const std::vector<Thread>& GetThreads() const { return this->_threads; }
            const uint TasksCount();
            SafeQueue<Pizza>& GetTasksDone();
            SafeQueue<Pizza>& GetPendingTasks();
        
        private:
            void RunTask(Thread* thread);

        private:
            uint _threadCount;
            std::mutex _mutex;
            FoodStock* _stock;
            std::vector<Thread> _threads;
            SafeQueue<Pizza> _tasks;
            SafeQueue<Pizza> _tasksDone;
            std::condition_variable _cv;
            bool _done;
    };
}


#endif /* !THREADPOOL_HPP_ */
