/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** StructsAndEnum
*/

#ifndef STRUCTSANDENUM_HPP_
#define STRUCTSANDENUM_HPP_

#include <iostream>
#include <algorithm>
#include <map>

namespace Plazza
{
    enum IgType
    {
        DOE, TOMATO, GRUYERE,
        HAM, MUSHROOMS, STEAK,
        EGGPLANT, GOATCHEESE,
        CHIEFLOVE, LIMIT
    };

    static const std::map<IgType, std::string> IngredientNameMap = {
        std::make_pair(IgType::DOE,         "Doe"),
        std::make_pair(IgType::TOMATO,      "Tomato"),
        std::make_pair(IgType::GRUYERE,     "Gruyere"),
        std::make_pair(IgType::HAM,         "Ham"),
        std::make_pair(IgType::MUSHROOMS,   "Mushrooms"),
        std::make_pair(IgType::STEAK,       "Steak"),
        std::make_pair(IgType::EGGPLANT,    "Eggplant"),
        std::make_pair(IgType::GOATCHEESE,  "Goatcheese"),
        std::make_pair(IgType::CHIEFLOVE,   "Chief luv <3"),
    };

    enum class PizzaType
    {
        Undefined   = (-1),
        Regina      = 1,
        Margarita   = 2,
        Americana   = 4,
        Fantasia    = 8
    };

    static const std::map<PizzaType, std::string> PizzaTypeMap = {
        std::make_pair(PizzaType::Regina,    "regina"),
        std::make_pair(PizzaType::Margarita, "margarita"),
        std::make_pair(PizzaType::Americana, "americana"),
        std::make_pair(PizzaType::Fantasia,  "fantasia"),
    };

    enum PizzaSize
    {
        U   = (-1),
        S   = 1,
        M   = 2,
        L   = 4,
        XL  = 8,
        XXL = 16
    };

    static const std::map<PizzaSize, std::string> PizzaSizeMap = {
        std::make_pair(PizzaSize::S,     "S"),
        std::make_pair(PizzaSize::M,     "M"),
        std::make_pair(PizzaSize::L,     "L"),
        std::make_pair(PizzaSize::XL,    "XL"),
        std::make_pair(PizzaSize::XXL,   "XXL"),
    };

    // Instruction type
    enum InstructionType
    {
        // Kitchen
        K_Availableness = 1,
        OrderCooked     = 2,
        K_closing       = 3,

        // Reception
        NewOrder        = 4,
        Status          = 5,
        CloseServer     = 6,

        // Server
        CloseKitchen    = 7,
        OrderReady      = 8,
    };

    struct OrderData
    {
        PizzaType Type = PizzaType::Undefined;
        PizzaSize Size = PizzaSize::U;
        uint PizzaNumber = 0;
        uint CookTime = 0;
        uint ID = (-1);

        bool operator==(const OrderData& other)
        {
            return (Type == other.Type
                && Size == other.Size
                && PizzaNumber
                && other.PizzaNumber
                && CookTime == other.CookTime);
        }
    };

    typedef struct PlazzaSendInstructions_s
    {
        InstructionType _i_type;
        OrderData       _o_data;
    } SendData_t;

    static const std::string refFile("./sources/IPC/.PlazzaIPC");
}

#endif /* !STRUCTSANDENUM_HPP_ */
