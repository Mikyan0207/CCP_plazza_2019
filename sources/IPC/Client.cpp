/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Client
*/

#include <IPC/Client.hpp>

namespace Plazza
{
    Client::Client(void)
    {
        this->_fd = (-1);
    }

    Client::Client(const int &fd, const sockaddr_un &s)
    {
        this->setSocket(fd, s);
    }

    Client::Client(const std::string &connectFile)
    {
        if ((this->_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == (-1))
            throw (SocketException("Error generating socket + fd."));
        this->_s_un.sun_family = AF_UNIX;
        strcpy(this->_s_un.sun_path, connectFile.c_str());
        this->updateFDSet();
    }

    void Client::connectToServer(void) const
    {
        int len = std::string(this->_s_un.sun_path).size() \
        + sizeof(this->_s_un.sun_family);

        if (connect(this->_fd, (sockaddr *)(&this->_s_un), len) == (-1))
            throw (SocketException("Error connecting to server."));
    }
}
