/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include <Cook.hpp>

namespace Plazza
{
    const uint Cook::Now()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds> \
        (std::chrono::_V2::system_clock::now().time_since_epoch()).count();
    }

    const uint Cook::GetDeltaTime(const uint& time)
    {
        auto now = Cook::Now();

        return (now - time);
    }

    bool Cook::CookPizza(const Plazza::Pizza &pizza, bool *forceStop)
    {
        std::chrono::milliseconds cookTime = std::chrono::milliseconds(pizza.getCookTime());
        auto time_point = Cook::Now();

        while (Cook::GetDeltaTime(time_point) < cookTime.count())
            if (*forceStop)
                return false;

        // std::stringstream ss;
        // ss << "\n\e[36m[Kitchen]\n\e[34mInfo:\e[39m \e[91mProcess(\e[39m" << getpid()
        //    << "\e[91m)\e[39m \e[35mThread(\e[39m"
        //    << std::this_thread::get_id()
        //    << "\e[35m)\e[39m"
        //    << std::endl
        //    << pizza.ToString() << "ms"
        //    << std::endl;
        // std::cout << ss.str();
        return true;
    }
}

