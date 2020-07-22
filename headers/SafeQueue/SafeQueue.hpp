/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <mutex>

#include <SafeQueue/ISafeQueue.hpp>
#include <Exceptions/Exception.hpp>

namespace Plazza
{
    template<typename T>
    class SafeQueue : public ISafeQueue<T>
    {
        public:
            SafeQueue() = default;
            ~SafeQueue() = default;

        public:
            void Push(const T& value);
            T Pop();
            bool TryPop(T& value);

            inline const int Size() const { return this->_queue.size(); }
            inline const bool IsEmpty() const { return this->_queue.empty(); };
            inline std::deque<T>& GetQueue() { return this->_queue; }

        private:
            std::deque<T> _queue;
            // std::queue<T> _queue;
            std::mutex _mutex;
    };
}

#include <SafeQueue/SafeQueue.inl>

#endif /* !SAFEQUEUE_HPP_ */
