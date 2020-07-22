/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <vector>
#include <algorithm>
#include "StructsAndEnum.hpp"

namespace Plazza
{
    class Pizza {
        public:
            Pizza() = default;
            Pizza(const OrderData &, const std::vector<IgType> &);
            ~Pizza() = default;

        public:
            const PizzaType &getType() const;
            const std::vector<IgType> &getIngredients() const;
            inline const PizzaSize &getSize() const { return this->_pizzaSize; };
            inline const uint &getCookTime() const { return this->_cookTime; };
            inline const uint &getID(void) const { return this->_id; };

        public:
            void addIngredient(const IgType &);
            void removeIngredient(const IgType &);
            const std::string ToString() const;

            explicit operator OrderData();

        protected:
            std::vector<IgType> _ings;
            uint _cookTime;
            PizzaSize _pizzaSize;
            PizzaType _type;
            uint _id;
    };
}

#endif /* !PIZZA_HPP_ */
