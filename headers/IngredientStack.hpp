/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IngredientStack
*/

#ifndef INGREDIENTSTACK_HPP_
#define INGREDIENTSTACK_HPP_

#include <iostream>
#include <chrono>

#include "../headers/StructsAndEnum.hpp"

namespace Plazza
{
    class IngredientStack {
        public:
            IngredientStack(const IgType &type);
            ~IngredientStack() = default;

        public:
            const bool pick(const uint &qt = 1);
            void refill(const uint &qt = 1);

        public:
            const IgType &getType(void) const;
            const uint getDeltaTimeMS(void) const;
            inline const uint &getQuantity(void) const { return (this->_quantity); };
            void setReloadStartTimeToNow(void);
            inline const bool &isReloading(void) const { return (this->_reloading); }

        private:
            IgType _type;
            uint _quantity;
            bool _reloading = false;
            std::chrono::milliseconds _reloadStartMS;
    };
}

#endif /* !INGREDIENTSTACK_HPP_ */
