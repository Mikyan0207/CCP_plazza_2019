/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#include <Pizza/Pizza.hpp>

namespace Plazza
{
    Pizza::Pizza(const OrderData &d, const std::vector<IgType> &ingredients)
    {
        this->_type = d.Type;
        this->_ings = ingredients;
        this->_pizzaSize = d.Size;
        this->_cookTime = d.CookTime;
        this->_id = d.ID;
    }

    const std::vector<IgType> &Pizza::getIngredients() const
    {
        return _ings;
    }

    const PizzaType &Pizza::getType() const
    {
        return _type;
    }

    void Pizza::addIngredient(const IgType &ing)
    {
        _ings.push_back(ing);
    }

    void Pizza::removeIngredient(const IgType &Ing)
    {
        _ings.erase(std::remove(_ings.begin(), _ings.end(), Ing), _ings.end());
    }

    Pizza::operator Plazza::OrderData()
    {
        OrderData data {};

        data.ID = _id;
        data.PizzaNumber = 1;
        data.Size = _pizzaSize;
        data.Type = _type;
        data.CookTime = _cookTime;

        return data;
    }

    const std::string Pizza::ToString() const
    {
        std::string pizzaString = "Pizza: ";

        switch (this->_type) {
            case PizzaType::Regina:
                pizzaString += "Regina"; break;
            case PizzaType::Americana:
                pizzaString += "Americana"; break;
            case PizzaType::Fantasia:
                pizzaString += "Fantasia"; break;
            case PizzaType::Margarita:
                pizzaString += "Margarita"; break;
            case PizzaType::Undefined:
                pizzaString += "Undefined"; break;
            default: break;
        }

        pizzaString += " \nSize: ";

        switch (this->_pizzaSize) {
            case PizzaSize::S:
                pizzaString += "S"; break;
            case PizzaSize::M:
                pizzaString += "M"; break;
            case PizzaSize::L:
                pizzaString += "L"; break;
            case PizzaSize::XL:
                pizzaString += "XL"; break;
            case PizzaSize::XXL:
                pizzaString += "XXL"; break;
            case PizzaSize::U:
                pizzaString += "U"; break;
            default: break;
        }

        pizzaString += "\nCookTime: ";
        pizzaString += std::to_string(this->_cookTime);

        return pizzaString;
    }
}
