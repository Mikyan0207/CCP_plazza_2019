/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <memory>
#include <vector>

#include <Cook.hpp>
#include <FoodStock.hpp>
#include <IPC/Client.hpp>
#include <Pizza/Pizza.hpp>
#include <Pizza/Americana.hpp>
#include <Pizza/Fantasia.hpp>
#include <Pizza/Margarita.hpp>
#include <Pizza/Regina.hpp>
#include <Process/IForkable.hpp>
#include <StructsAndEnum.hpp>
#include <Thread/Thread.hpp>
#include <Thread/ThreadPool.hpp>

namespace Plazza
{
    class Kitchen : public IForkable
    {
        public:
            Kitchen(const uint &reloadTimeMS, const uint &cpk);
            ~Kitchen() final;
            void connectToDataCenter(void);
        
        public:
            void Run() final;
            void AutoClose();
            void ProcessOrders();
            const Pizza GetPizza(const OrderData& order);
        
        private:
            void checkUp(void);
            void sendStatus(void);
            void sendAvailableness(void);
            void interpretData(const SendData_t &d);
            void SendCookedPizza();

        private:
            std::unique_ptr<FoodStock> _stock;
            std::unique_ptr<ThreadPool> _pool;
            Client _cli;
            bool _open = true;
            std::chrono::seconds _lastActivity;
    };
}


#endif /* !KITCHEN_HPP_ */
