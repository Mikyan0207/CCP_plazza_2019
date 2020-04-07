/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Order
*/

#ifndef ORDER_HPP_
#define ORDER_HPP_

#include <string>

namespace Plazza
{
    // Pack ?
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    // Pack ?
    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    // Pack ?
    struct OrderData
    {
        PizzaType Type;
        PizzaSize Size;
        uint PizzaNumber;
    };
}


#endif /* !ORDER_HPP_ */
