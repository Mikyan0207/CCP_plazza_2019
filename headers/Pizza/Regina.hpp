/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Regina
*/

#ifndef REGINA_HPP_
#define REGINA_HPP_

#include "Pizza.hpp"

namespace Plazza
{
    class Regina : public Pizza {
        public:
            Regina(const OrderData &d) :
            Pizza(d, std::vector<IgType>{
                IgType::DOE, IgType::TOMATO,
                IgType::GRUYERE, IgType::HAM,
                IgType::MUSHROOMS
            }) {}
            ~Regina() = default;

        protected:
        private:
    };
}

#endif /* !REGINA_HPP_ */
