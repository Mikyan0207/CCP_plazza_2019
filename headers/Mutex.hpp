/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Mutex
*/

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include "IMutex.hpp"

namespace Plazza
{
    class Mutex : public IMutex
    {
        public:
            Mutex();
            ~Mutex();

        public:
            void Lock();
            void Unlock();
            bool TryLock();

        public:
            inline const std::mutex& GetMutex() const { return this->_mutex; };

        private:
            std::mutex _mutex;
    };
}

#endif /* !MUTEX_HPP_ */
