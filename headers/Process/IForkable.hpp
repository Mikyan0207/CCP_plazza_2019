/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IForkable
*/

#ifndef IFORKABLE_HPP_
#define IFORKABLE_HPP_

namespace Plazza
{
    class IForkable {
        public:
            virtual ~IForkable() {};

        public:
            virtual void Run() = 0;
    };
}


#endif /* !IFORKABLE_HPP_ */
