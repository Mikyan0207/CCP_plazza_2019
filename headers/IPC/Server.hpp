/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "Client.hpp"
#include <vector>

namespace Plazza
{
    class Server : public Socket {
        public:
            Server(const uint &maxClient, const std::string &connectFile);
            ~Server() = default;

        public: // Getters
            inline fd_set getFDSet(void) const { return (this->_readfds); };
            inline const int &getFDMax(void) const { return (this->_maxFD); };
            const std::vector<Plazza::Client> &getClientList(void);

        public:
            Client acceptClient(void);
            void waitForActivity(void);
            const int checkNewConnection(void);
            void checkForNewData(void);
            void updateFDSet(void);
            void sendData(const SendData_t &d, const int &fd) const;
            void closeServer(void);

        protected:
            const uint _maxClient = 42;
            std::vector<Plazza::Client> _clientList;
            bool _closed = false;
    };
}

#endif /* !SERVER_HPP_ */
