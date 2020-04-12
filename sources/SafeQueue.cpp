/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SafeQueue
*/

#include "SafeQueue.hpp"

template<typename T>
void Plazza::SafeQueue<T>::Push(const T& value)
{
    if (this->_mutex.TryLock())
    {
        this->_queue.push(value);
        this->_mutex.Unlock();
    }
    else
    {
        // throw ?
    }

}

template<typename T>
bool Plazza::SafeQueue<T>::TryPop(T& value)
{
    if (this->_mutex.TryLock())
    {
        if (this->_queue.empty())
        {
            this->_mutex.Unlock();
            return false;
        }

        value = this->_queue.pop();
        this->_mutex.Unlock();

        return true;
    }
    else
    {
        // throw ?
    }

    return false;
}