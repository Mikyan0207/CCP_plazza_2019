/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** IThread
*/

#ifndef ITHREAD_HPP_
#define ITHREAD_HPP_

#include <thread>

namespace Plazza
{
    class IThread
    {
        public:
            virtual ~IThread() = default;
            virtual void Wait() = 0;
            virtual const std::thread& GetThread() const = 0;
    };
}

#endif /* !ITHREAD_HPP_ */
