/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <string>

namespace Plazza
{
    class Exception {
        public:
            Exception(const std::string &what);
            ~Exception() = default;

        public:
            inline const char *what() const throw() { return _what.c_str(); };

        protected:
            const std::string _what;
    };

    class InitException : public Exception {
        public:
            InitException(const std::string &what);
            ~InitException() = default;
    };

    class OrderException : public Exception {
        public:
            OrderException(const std::string &what);
            ~OrderException() = default;
    };

    class ServerException : public Exception {
        public:
            ServerException(const std::string &what);
            ServerException() = default;
    };

    class SocketException : public Exception {
        public:
            SocketException(const std::string &what);
            SocketException() = default;
    };
}

#endif /* !EXCEPTION_HPP_ */
