#pragma once

#include "SafeQueue.hpp"

namespace Plazza
{
    template<typename T>
    void SafeQueue<T>::Push(const T& value)
    {
        if (this->_mutex.try_lock()) {
            this->_queue.push_back(value);
            this->_mutex.unlock();
        }
    }

    template<typename T>
    T SafeQueue<T>::Pop()
    {
        if (this->_mutex.try_lock()) {
            T value = this->_queue.front();
            this->_queue.pop_front();
            this->_mutex.unlock();
            return value;
        } else {
            throw Plazza::Exception("Failed to lock mutex");
        }
    }

    template<typename T>
    bool SafeQueue<T>::TryPop(T& value)
    {
        if (this->_mutex.try_lock()) {
            if (this->_queue.empty()) {
                this->_mutex.unlock();
                return false;
            }

            value = this->_queue.front();
            this->_queue.pop_front();
            this->_mutex.unlock();

            return (true);
        }

        return (false);
    }
}