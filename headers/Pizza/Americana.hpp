/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Americana
*/

#ifndef AMERICANA_HPP_
#define AMERICANA_HPP_

#include "Pizza.hpp"

namespace Plazza
{
    class Americana : public Pizza {
        public:
            Americana(const OrderData &d) :
            Pizza(d, std::vector<IgType>{
                IgType::DOE, IgType::TOMATO,
                IgType::GRUYERE, IgType::STEAK
            }) {}
            ~Americana() = default;

        protected:
        private:
    };
}

#endif /* !Americana_HPP_ */
