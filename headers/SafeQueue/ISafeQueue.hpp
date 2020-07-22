/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ISafeQueue
*/

#ifndef ISAFEQUEUE_HPP_
#define ISAFEQUEUE_HPP_

#include <queue>

namespace Plazza
{
    template<typename T>
    class ISafeQueue
    {
        public:
            virtual ~ISafeQueue() = default;
            virtual void Push(const T& value) = 0;
            virtual bool TryPop(T& value) = 0;
    };
}

#endif /* !ISAFEQUEUE_HPP_ */
