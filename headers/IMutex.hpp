/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** IMutex
*/

#ifndef IMUTEX_HPP_
#define IMUTEX_HPP_

#include <mutex>
#include <string>

namespace Plazza
{
    class IMutex
    {
        public:
            virtual ~IMutex() = default;
            virtual void Lock() = 0;
            virtual void Unlock() = 0;
            virtual bool TryLock() = 0;
    };
}


#endif /* !IMUTEX_HPP_ */
