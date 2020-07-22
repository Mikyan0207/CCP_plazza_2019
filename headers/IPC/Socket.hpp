/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <string>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <StructsAndEnum.hpp>
#include <Exceptions/Exception.hpp>

namespace Plazza
{
    class Socket {
        public:
            enum mode { SERVER, CLIENT };

        public:
            Socket(const mode &m = mode::CLIENT);
            void updateFDSet(void);
            void checkForNewData(void);
            void closeSocketDescr(void);
            void sendData(const SendData_t &d) const;
            ~Socket() = default;
        
        public:
            // Getters
            inline const int &getSockDescr(void) const { return (this->_fd); };
            inline const sockaddr_un &getSockAddr(void) const { return (this->_s_un); };
            inline const mode &getMode(void) const { return (this->_mode); };
            inline const fd_set &getFDSet(void) const { return (this->_readfds); };

            // Setters
            void setSocket(const int &fd, const sockaddr_un &s_un);
        
        public:
            void operator=(const Plazza::Socket &cp);

        protected:
            int _fd = (-1);
            sockaddr_un _s_un;
            mode _mode;
            fd_set _readfds;
            int _maxFD;
            char _rData[1025];
    };
}

#endif /* !SOCKET_HPP_ */
