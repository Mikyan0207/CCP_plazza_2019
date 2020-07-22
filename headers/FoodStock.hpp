/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** FoodStock
*/

#ifndef FOODSTOCK_HPP_
#define FOODSTOCK_HPP_

#include <vector>
#include <IngredientStack.hpp>

namespace Plazza
{
    class FoodStock {
        public:
            FoodStock() = default;
            FoodStock(const uint &reloadTimeMS);
            FoodStock(const FoodStock& foodStock);
            const bool getIngredient(const Plazza::IgType &t);
            void update(void);
            FoodStock &operator=(const FoodStock& other);
            const std::map<std::string, int> getStockStatus(void);
            ~FoodStock() = default;

        private:
            std::vector<IngredientStack> _ingredients;
            uint _reloadTimeMS;
    };
}

#endif /* !FOODSTOCK_HPP_ */
