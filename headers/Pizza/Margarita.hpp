/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Margarita
*/

#ifndef MARGARITA_HPP_
#define MARGARITA_HPP_

#include "Pizza.hpp"

namespace Plazza
{
    class Margarita : public Pizza {
        public:
            Margarita(const OrderData &d) :
            Pizza(d, std::vector<IgType>{
                IgType::DOE, IgType::TOMATO, IgType::GRUYERE
            }) {}
            ~Margarita() = default;

        protected:
        private:
    };
}

#endif /* !Margarita_HPP_ */
