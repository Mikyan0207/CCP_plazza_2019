/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fantasia
*/

#ifndef FANTASIA_HPP_
#define FANTASIA_HPP_

#include "Pizza.hpp"

namespace Plazza
{
    class Fantasia : public Pizza {
        public:
            Fantasia(const OrderData &d) :
            Pizza(d, std::vector<IgType>{
                IgType::DOE, IgType::TOMATO,
                IgType::EGGPLANT, IgType::GOATCHEESE,
                IgType::CHIEFLOVE
            }) {}
            ~Fantasia() = default;

        protected:
        private:
    };
}

#endif /* !Fantasia_HPP_ */
