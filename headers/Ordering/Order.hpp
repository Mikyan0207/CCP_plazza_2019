/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Order
*/

#ifndef ORDER_HPP_
#define ORDER_HPP_

#include "../StructsAndEnum.hpp"
#include <iostream>
#include <array>

namespace Plazza
{
    class Order {
        public:
            Order(const OrderData &oData);
            void addPizza(const uint &n);
            const bool &isReady(void) const;
            ~Order() = default;

        public:
            inline const PizzaType &getPizzaType(void) const { return (this->_type); };
            inline const PizzaSize &getPizzaSize(void) const { return (this->_size); };
            inline const uint &getID(void) const { return (this->_id); };
            inline const std::array<uint, 2> &getPizzaNumber(void) const { return (this->_pizzaNumber); };
            const OrderData getStruct(void) const;

        private:
            PizzaType _type;
            PizzaSize _size;
            std::array<uint, 2> _pizzaNumber = {0, 0};
            uint _cookingTime;
            uint _id;
            bool _ready = false;
    };
}

std::ostream &operator<<(std::ostream &out, const Plazza::Order &order);

#endif /* !ORDER_HPP_ */