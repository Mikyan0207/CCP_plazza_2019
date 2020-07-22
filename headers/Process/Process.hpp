/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <iostream>
#include <unistd.h>
#include <signal.h>

#include <Exceptions/Exception.hpp>
#include <Process/IForkable.hpp>
#include <Kitchen.hpp>

namespace Plazza
{
    class Process {
        public:
            Process(IForkable &);
            inline const int &getChildPID(void) const { return (this->_processId); }
            ~Process() = default;

        private:
            pid_t _processId;
    };
}

#endif /* !PROCESS_HPP_ */
