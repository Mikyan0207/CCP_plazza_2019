/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Server
*/

#include <IPC/Server.hpp>

namespace Plazza
{
    Server::Server(const uint &maxClient, const std::string &connectFile) :
    Socket::Socket(mode::SERVER), _maxClient(maxClient)
    {
        int len;

        if ((this->_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == (-1))
            throw (ServerException("Error generating master socket."));
        this->_s_un.sun_family = AF_UNIX;
        strcpy(this->_s_un.sun_path, connectFile.c_str());
        unlink(this->_s_un.sun_path);
        len = std::string(this->_s_un.sun_path).size() + sizeof(this->_s_un.sun_family);
        if (bind(this->_fd, (sockaddr *)(&this->_s_un), len) == (-1))
            throw (ServerException("Error binding master socket to file."));
        if (listen(this->_fd, this->_maxClient) == (-1))
            throw (ServerException("Error setting server to listening."));
        // std::cout << "[SERVER] - Ready for connection..." << std::endl;
    }

    Client Server::acceptClient(void)
    {
        int newfd;
        sockaddr_un newCStruct;
        socklen_t sSize = sizeof(newCStruct);
        Client nClient;

        if ((newfd = accept(this->_fd, (sockaddr *)(&newCStruct), &sSize)) == (-1))
            throw (ServerException("Error accepting new client connexion."));
        nClient.setSocket(newfd, newCStruct);
        this->_clientList.push_back(nClient);
        // std::cout << "[SERVER] - Connection established with [" << nClient.getSockDescr() \
        // << "] (socket descriptor)." << std::endl;
        return (nClient);
    }

    void Server::updateFDSet(void)
    {
        FD_ZERO(&(this->_readfds));
        FD_SET(this->_fd, &(this->_readfds));

        this->_maxFD = this->_fd;
        for (auto &sockD : this->_clientList) {
            FD_SET(sockD.getSockDescr(), &(this->_readfds));
            this->_maxFD = (sockD.getSockDescr() > this->_maxFD) ? sockD.getSockDescr() : this->_maxFD;
        }
    }

    void Server::waitForActivity(void)
    {
        // std::cout << "Waiting in select..." << std::endl;
        int activity = select(this->_maxFD + 1, &(this->_readfds), NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
            std::cerr << "Select error" << std::endl;
    }

    const int Server::checkNewConnection(void)
    {
        // std::cout << "{" << std::endl;
        if (FD_ISSET(this->_fd, &(this->_readfds))) {
            // std::cout << "\tNew client detected... accepting..." << std::endl;
            Client c = this->acceptClient();
            // std::cout << "\tNew client added successfully !\n}" << std::endl;
            return (c.getSockDescr());
        }
        // std::cout << "\tNo new client... moving to next step.\n}" << std::endl;
        return (-1);
    }

    void Server::checkForNewData(void)
    {
        int removed = 0;
        int lenread = 0;

        for (auto elem = this->_clientList.begin(); \
        elem != this->_clientList.end(); ++elem)
            if (FD_ISSET(elem->getSockDescr(), &(this->_readfds))) {
                if ((lenread = read(elem->getSockDescr(), this->_rData, 1024)) == 0) {
                    elem->closeSocketDescr();
                    this->_clientList.erase(elem);
                    removed = 1;
                    // std::cout << "[SERVER] - A client has disconnected." << std::endl;
                    break;
                } else {
                    this->_rData[lenread] = 0;
                    // Do whatever you need with the
                    // data stored in this->_rData.
                }
            }
        if (removed) // may need to actualize fd_set and run another select
            this->checkForNewData();
    }

    const std::vector<Client> &Server::getClientList(void)
    {
        for (auto &elem : this->_clientList)
            elem.closeSocketDescr();
        return (this->_clientList);
    }

    void Server::sendData(const SendData_t &d, const int &fd) const
    {
        for (const auto &elem : this->_clientList)
            if (elem.getSockDescr() == fd) {
                elem.sendData(d);
                return;
            }
        throw (ServerException("This fd(" + std::to_string(fd) \
        + ") is not associated to a current client."));
    }

    void Server::closeServer(void)
    {
        for (auto &elem : this->_clientList)
            elem.closeSocketDescr();
        this->_closed = true;
    }
}