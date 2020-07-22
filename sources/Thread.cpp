/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Thread
*/

#include <Thread/Thread.hpp>

namespace Plazza
{
    Thread::~Thread()
    {
        this->Wait();
    }

    void Thread::Wait()
    {
        if (this->_thread.joinable())
            this->_thread.join();
    }
}
