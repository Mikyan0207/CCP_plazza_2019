/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <IPC/Socket.hpp>

namespace Plazza
{
    class Client : public Socket {
        public:
            Client();
            Client(const int &, const sockaddr_un &);
            Client(const std::string &connectFile);
            ~Client() = default;

        public:
            void connectToServer(void) const;
    };
}

#endif /* !CLIENT_HPP_ */
