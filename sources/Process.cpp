/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#include <Process/Process.hpp>

namespace Plazza
{
    Process::Process(IForkable &forkableClass)
    {
        this->_processId = fork();

        if (this->_processId == -1)
            throw Plazza::Exception("Fork failed.");

        if (this->_processId == 0) {
            forkableClass.Run();
            forkableClass.~IForkable();
            std::exit(0);
        }
    }
}