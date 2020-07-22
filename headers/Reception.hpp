/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <chrono>
#include <ctime>

#include <Process/IForkable.hpp>
#include <SafeQueue/SafeQueue.hpp>
#include "StructsAndEnum.hpp"
#include <Exceptions/Exception.hpp>
#include "IPC/Server.hpp"

namespace Plazza
{
    class Reception : public IForkable {
        public:
            Reception();
            Reception(const float &ctm, const int &cpk, const double &rt);
            ~Reception() = default;

        public: // General
            void Run() final;
            void connectToDataCenter(void);
            const int loop(void);

        public: // Setters
            void setCookingTimeMultiplier(const float &ctm);
            void setCooksNbPerKitchen(const int &cpk);
            void setIngredientreplaceTime(const double &irt);
            void setArgumentsFromTab(char **av);

        public: // Getters
            inline const float &getCookingTimeMultiplier(void) const { return (this->_cookingTimeMultiplier); };
            inline const uint &getCooksNbPerKitchen(void) const { return (this->_cooksPerKitchen); };
            inline const double &getIngredientreplaceTime(void) const { return (this->_replaceTimeMS); };

        private: // Private functions
            void initMaps(void);
            const std::string &clearString(std::string &str);
            void getOrderFromCurrentInput(void);
            void giveOrdersToKitchens(void);
            void storeOrder(const std::string &s);
            void closePizzeria(void);
            const bool checkUp(void);
            void announceOrder(const OrderData &d);

        private: // Program start variables
            float   _cookingTimeMultiplier = 0;
            uint    _cooksPerKitchen = 0;
            double  _replaceTimeMS = 0;
            size_t  _commandNb = 0;

        private:
            std::ofstream _logFile;
            std::string _input;
            std::vector<OrderData> _orders;
            std::map<Plazza::PizzaType, uint> _cookingTimeMapMS;
            bool _open = true;
        
        private: // IPC Variables
            Client _cli;
            fd_set _readfds;
            SendData_t _sData;
    };
}

#endif /* !RECEPTION_HPP_ */