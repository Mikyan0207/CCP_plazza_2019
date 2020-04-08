/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <memory>
#include <iostream>
#include "IThread.hpp"
#include "Mutex.hpp"

namespace Plazza
{
    template<typename T>
    class Thread : public IThread
    {
        public:
            Thread(T (*function)())
            {
                this->_thread = std::thread(function);
            };

            template<typename ... Targs>
            Thread(T (*function)(Targs... args), Targs... args)
            {
                this->_thread = std::thread(function, args...);
            };

            ~Thread() = default;

        public:
            void Wait()
            {
                if (this->_thread.joinable())
                {
                    this->_thread.join();
                }
            };

        public:
            inline const std::thread& GetThread() const { return this->_thread; };

        private:
           std::thread _thread;
           Mutex _mutex;
    };
}


#endif /* !THREAD_HPP_ */
