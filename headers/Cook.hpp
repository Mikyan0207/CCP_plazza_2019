/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <unistd.h>

#include <Pizza/Pizza.hpp>
#include <StructsAndEnum.hpp>

namespace Plazza
{
    class Cook
    {
        public:
            static const uint GetDeltaTime(const uint& time);
            static const uint Now();
            static bool CookPizza(const Pizza& pizza, bool* forceStop);
    };
}

#endif /* !COOK_HPP_ */
