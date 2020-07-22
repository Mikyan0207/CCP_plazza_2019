/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Exception
*/

#include <Exceptions/Exception.hpp>

namespace Plazza
{
    Exception::Exception(const std::string &what) : _what(what) {}

    InitException::InitException(const std::string &what) :
    Exception::Exception("[Initialization Exception] - " + what) {}

    SocketException::SocketException(const std::string &what) :
    Exception::Exception("[Socket Exception] - " + what) {}

    ServerException::ServerException(const std::string &what) :
    Exception::Exception("[Server Exception] - " + what) {}

    OrderException::OrderException(const std::string &what) :
    Exception::Exception("[Order Exception] - " + what) {}
}