/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** FoodStock
*/

#include <FoodStock.hpp>

namespace Plazza
{
    FoodStock::FoodStock(const uint &reloadTimeMS) :
    _reloadTimeMS(reloadTimeMS)
    {
        for (uint idx = 0; idx < IgType::LIMIT; ++idx)
            this->_ingredients.push_back(
                IngredientStack(static_cast<IgType>(idx))
            );
    }

    FoodStock::FoodStock(const FoodStock& other)
    {
        this->_ingredients = other._ingredients;
        this->_reloadTimeMS = other._reloadTimeMS;
    }

    const bool FoodStock::getIngredient(const IgType &t)
    {
        this->update();
        for (auto &elem : this->_ingredients)
            if (elem.getType() == t)
                return (elem.pick());
        // std::cerr << "[ERROR] - Non existent ingredient was asked." << std::endl;
        return (false);
    }

    const std::map<std::string, int> FoodStock::getStockStatus(void)
    {
        std::map<std::string, int> tmp;

        for (const auto &elem : this->_ingredients) {
            tmp.insert(std::make_pair(
                IngredientNameMap.at(elem.getType()),
                elem.getQuantity()
            ));
        }
        return (tmp);
    }

    FoodStock& FoodStock::operator=(const FoodStock& other)
    {
        this->_ingredients = other._ingredients;
        this->_reloadTimeMS = other._reloadTimeMS;
        return *this;
    }

    void FoodStock::update(void)
    {
        for (auto &elem : this->_ingredients)
            if (elem.isReloading() && elem.getDeltaTimeMS() > this->_reloadTimeMS)
                elem.refill(1);
    }
}
