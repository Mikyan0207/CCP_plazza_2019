/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Thread
*/

#include "Thread.hpp"

template<typename T>
Plazza::Thread<T>::~Thread()
{
    if (this->_status == Plazza::DEAD)
        this->_thread.detach();
}

template<typename T>
void Plazza::Thread<T>::Start()
{
    // ?
}

template<typename T>
void Plazza::Thread<T>::Stop()
{
    if (this->_status != Plazza::DEAD)
    {
        this->_thread.detach();
        this->_status = Plazza::DEAD;
    }
}

template<typename T>
void Plazza::Thread<T>::Wait()
{
    if (this->_status == Plazza::RUNNING)
    {
        this->_thread.join();
        this->_status = Plazza::STARTED;
    }
}

template class Plazza::Thread<void>;