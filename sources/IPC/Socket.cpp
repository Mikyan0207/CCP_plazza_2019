/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Socket
*/

#include <IPC/Socket.hpp>

namespace Plazza
{
    Socket::Socket(const mode &m) : _mode(m) {}

    void Socket::setSocket(const int &fd, const sockaddr_un &s_un)
    {
        this->_fd = fd;
        this->_s_un = s_un;
    }

    void Socket::operator=(const Socket &cp)
    {
        this->_fd = cp.getSockDescr();
        this->_s_un = cp.getSockAddr();
        this->_mode = cp.getMode();
        this->updateFDSet();
    }

    void Socket::updateFDSet(void)
    {
        FD_ZERO(&(this->_readfds));
        FD_SET(this->_fd, &(this->_readfds));

        this->_maxFD = this->_fd;
    }

    void Socket::checkForNewData(void)
    {
        int lenread = 0;

        if (FD_ISSET(this->_fd, &(this->_readfds))) {
            if ((lenread = read(this->_fd, this->_rData, 1024)) == 0) {
                this->closeSocketDescr();
            } else {
                this->_rData[lenread] = 0;
                std::cout << "Received: " << this->_rData << std::endl;
            }
        }
    }

    void Socket::sendData(const SendData_t &d) const
    {
        if (write(this->_fd, &d, sizeof(SendData_t)) == (-1))
            throw (SocketException("Couldn't write data in fd = [" \
            + std::to_string(this->_fd) + "]."));
    }

    void Socket::closeSocketDescr(void)
    {
        if (this->_fd > 0) {
            // std::cout << "Closing socket descriptor [" << this->_fd << "]" << std::endl;
            close(this->_fd);
            this->_fd = (-1);
        }
    }
}
