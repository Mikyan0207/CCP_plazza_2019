/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Order
*/

#include "../../headers/Ordering/Order.hpp"

namespace Plazza
{
    Order::Order(const OrderData &oData)
    {
        this->_type = oData.Type;
        this->_size = oData.Size;
        this->_pizzaNumber = std::array<uint, 2>{0, oData.PizzaNumber};
        this->_cookingTime = oData.CookTime;
        this->_id = oData.ID;
    }

    void Order::addPizza(const uint &n)
    {
        this->_pizzaNumber[0] += n;
        if (this->_pizzaNumber[0] >= this->_pizzaNumber[1])
            this->_ready = true;
    }

    const bool &Order::isReady(void) const
    {
        return (this->_ready);
    }

    const OrderData Order::getStruct(void) const
    {
        return (OrderData {
            this->_type,
            this->_size,
            this->_pizzaNumber[1],
            this->_cookingTime,
            this->_id
        });
    }
}

std::ostream &operator<<(std::ostream &out, const Plazza::Order &order)
{
    const auto &nbs = order.getPizzaNumber();

    out << "Order ID = [" << order.getID() << "]\n{" << std::endl;
    out << "\tType:\t" << Plazza::PizzaTypeMap.at(order.getPizzaType()) << std::endl;
    out << "\tSize:\t" << Plazza::PizzaSizeMap.at(order.getPizzaSize()) << std::endl;
    out << "\tCooked:\t" << nbs[0] << " / " << nbs[1] << std::endl;
    out << "}" << std::endl;
    return (out);
}