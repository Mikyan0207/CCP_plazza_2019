/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <atomic>
#include <condition_variable>
#include <iostream>

#include <Pizza/Pizza.hpp>
#include <StructsAndEnum.hpp>
#include <Thread/IThread.hpp>

namespace Plazza
{
    class Thread : public IThread
    {
        public:
            Thread() = default;
            Thread(const Thread& other) {}
            ~Thread();

        public:
            template<typename T, typename ... Targs>
            void Run(T&& function, Targs&& ... args);
            void Wait();

        public:
            inline const std::thread& GetThread() const { return this->_thread; };
            inline void SetActive(const bool& state) { this->_isActive.store(state); };
            inline const bool IsActive() const { return this->_isActive.load(); };

        private:
            std::thread _thread;
            std::atomic<bool> _isActive = false;
    };
}

#include <Thread/Thread.inl>

#endif /* !THREAD_HPP_ */
