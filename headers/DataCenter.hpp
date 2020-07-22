/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** DataCenter
*/

#ifndef DATACENTER_HPP_
#define DATACENTER_HPP_

#include <memory>
#include <sys/wait.h>

#include <IPC/Server.hpp>
#include <Kitchen.hpp>
#include <Ordering/Order.hpp>
#include <Process/Process.hpp>
#include <StructsAndEnum.hpp>

namespace Plazza
{
    class DataCenter : public Server {
        public:
            DataCenter(const uint &srt, const uint &cpk,
            const std::string &connectFile = Plazza::refFile);
            ~DataCenter() = default;

        public:
            void manageData(void);
            void checkForNewData(void);

        private:
            void displayOrders(void) const;
            void dealOrders(const OrderData &);
            const bool interpretData(const SendData_t &);
            void updateCurrentOrders(const OrderData &);
            void cleanCurrentOrders(void);
            void createKitchen(void);
            void actualizeKitchenStatus(void);

        private:
            const uint _stockReloadTime;
            const uint _cooksPerKitchen;

        private:
            int _receptionFD;
            SendData_t _data;
            std::vector<Order> _currentOrders;
            std::vector<OrderData> _orderStack;
            std::map<int, int> _kitchens;   // <fd, currentOrderNb>
            // std::map<int, int> _k_ids;      // <fd, PID>
            int _receptions;
    };
}

#endif /* !DATACENTER_HPP_ */
