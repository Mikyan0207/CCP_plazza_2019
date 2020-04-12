/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include "ISafeQueue.hpp"
#include "Mutex.hpp"

namespace Plazza
{
    template<typename T>
    class SafeQueue : public ISafeQueue<T>
    {
        public:
            SafeQueue() { };
            ~SafeQueue() = default;

        public:
            void Push(const T& value);
            bool TryPop(T& value);

        private:
            std::queue<T> _queue;
            Mutex _mutex;
    };
}

#endif /* !SAFEQUEUE_HPP_ */
