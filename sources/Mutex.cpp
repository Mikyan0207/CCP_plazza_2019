/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Mutex
*/

#include "Mutex.hpp"

Plazza::Mutex::Mutex()
{
}

Plazza::Mutex::~Mutex()
{
}

void Plazza::Mutex::Lock()
{
    this->_mutex.lock();
}

void Plazza::Mutex::Unlock()
{
    this->_mutex.unlock();
}

bool Plazza::Mutex::TryLock()
{
    if (this->_mutex.try_lock())
        return true;

    return false;
}