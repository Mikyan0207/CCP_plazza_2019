/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IngredientStack
*/

#include <IngredientStack.hpp>

namespace Plazza
{
    IngredientStack::IngredientStack(const IgType &type) :
    _type(type), _quantity(5), _reloading(false) {}

    const bool IngredientStack::pick(const uint &qt)
    {
        if (qt <= this->_quantity) {
            if (this->_quantity == 5) {
                this->setReloadStartTimeToNow();
                this->_reloading = true;
            }
            this->_quantity -= qt;
            return (true);
        }
        // std::cerr << "[ERROR] - Not enough product in the ingredient stack." << std::endl;
        return (false);
    }

    void IngredientStack::refill(const uint &qt)
    {
        this->_quantity += qt;
        if (this->_quantity >= 5) {
            this->_quantity = 5;
            this->_reloading = false;
        }
        this->setReloadStartTimeToNow();
    }

    // ~~~~~~~~~~~~~ StockManagement ~~~~~~~~~~~~~ //

    const IgType &IngredientStack::getType(void) const
    {
        return (this->_type);
    }

    void IngredientStack::setReloadStartTimeToNow(void)
    {
        this->_reloadStartMS = \
        std::chrono::duration_cast<std::chrono::milliseconds> \
        (std::chrono::_V2::system_clock::now().time_since_epoch());
    }

    const uint IngredientStack::getDeltaTimeMS(void) const
    {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>\
        (std::chrono::_V2::system_clock::now().time_since_epoch());

        return (now.count() - this->_reloadStartMS.count());
    }
}

