/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** DataCenter
*/

#include "DataCenter.hpp"

namespace Plazza
{
    DataCenter::DataCenter(const uint &srt,
    const uint &cpk, const std::string &connectFile) :
    Server::Server(100, connectFile),
    _stockReloadTime(srt), _cooksPerKitchen(cpk) {}

    void DataCenter::manageData(void)
    {
        int tmp_fd = (-1);

        { // Connect to reception first
            this->updateFDSet();
            this->waitForActivity();
            this->_receptionFD = this->checkNewConnection();
        }
        while (!this->_closed) {
            this->updateFDSet();
            this->waitForActivity();
            if ((tmp_fd = this->checkNewConnection()) != (-1))
                this->_kitchens.insert(std::make_pair(tmp_fd, 0));
            this->checkForNewData();
        }
    }

    void DataCenter::checkForNewData(void)
    {
        int mod = 0;

        // std::cout << "{" << std::endl;
        for (auto elem = this->_clientList.begin(); \
        !this->_closed && elem != this->_clientList.end(); ++elem)
            if (FD_ISSET(elem->getSockDescr(), &(this->_readfds))) {
                // std::cout << "\tReading from : " << elem->getSockDescr() << std::endl;
                if ((read(elem->getSockDescr(), &(this->_data), sizeof(SendData_t))) == 0) {
                    this->_kitchens.erase(elem->getSockDescr());
                    // this->_k_ids.erase(elem->getSockDescr());
                    elem->closeSocketDescr();
                    this->_clientList.erase(elem);
                    mod = 1; break;
                } else if (this->_data._i_type == InstructionType::K_Availableness) {
                    this->_kitchens.at(elem->getSockDescr()) = this->_data._o_data.PizzaNumber;
                    // std::cout << "\tData set to : " << this->_kitchens.at(elem->getSockDescr()) << std::endl;
                } else if (this->_data._i_type == InstructionType::K_closing && \
                this->_data._o_data.ID != getpid()) {
                    waitpid(this->_data._o_data.ID, nullptr, 0);
                } else if (this->interpretData(this->_data))
                    mod = 1; break;
            }
        // std::cout << "}" << std::endl;
        if (mod && !this->_closed) {
            this->updateFDSet();
            this->waitForActivity();
            this->checkForNewData();
        }
    }

    ////////////////////// Private Zone //////////////////////

    void DataCenter::cleanCurrentOrders(void)
    {
        std::vector<std::vector<Plazza::Order>::iterator> oDone;

        for (auto elem = _currentOrders.begin(); \
        elem != _currentOrders.end() ; ++elem)
            if (elem->isReady()) {
                this->_data = {
                    InstructionType::OrderReady,
                    elem->getStruct()
                };
                // std::cout << "[DATAC] - Order ready. Sending to reception..." << std::endl;
                this->sendData(this->_data, this->_receptionFD);
                oDone.push_back(elem);
            }
        for (auto &elem : oDone)
            this->_currentOrders.erase(elem);
    }

    void DataCenter::updateCurrentOrders(const OrderData &data)
    {
        // std::cout << "[DATAC] - Updating Orders" << std::endl;
        for (auto &elem : this->_currentOrders)
            if (data.ID == elem.getID()) {
                elem.addPizza(data.PizzaNumber);
                break;
            }
        this->cleanCurrentOrders();
    }

    void DataCenter::displayOrders(void) const
    {
        int idx = 1;
        uint time_point;
        SendData_t d = {InstructionType::Status, OrderData()};

        // std::cout << "[DATAC] - Asked for status" << std::endl;
        for (const auto &elem : this->_currentOrders)
            std::cout << elem << std::endl;
        for (const auto &elem : this->_kitchens) {
            time_point = Cook::Now();
            std::cout << "\nKitchen #" << idx << std::endl << std::endl;
            this->sendData(d, elem.first);
            while (Cook::GetDeltaTime(time_point) < 5);
            idx += 1;
        }
    }

    void DataCenter::createKitchen(void)
    {
        int tmp_fd = (-1);
        Kitchen k(this->_stockReloadTime, this->_cooksPerKitchen);
        Process nKitch(k); // Creation of a new process

        { // Wait for new kitchen to connect before continuing
            FD_ZERO(&(this->_readfds));
            FD_SET(this->_fd, &(this->_readfds));
            this->_maxFD = this->_fd;

            this->waitForActivity();
            if ((tmp_fd = this->checkNewConnection()) != (-1)) {
                this->_kitchens.insert(std::make_pair(tmp_fd, 0));
            }
            this->updateFDSet();
        }
    }

    void DataCenter::dealOrders(const OrderData &oData)
    {
        int full = false;
        std::vector<Plazza::Client>::iterator itK;

        if (this->_kitchens.size() == 0) // Create client if there is none
            this->createKitchen();
        { // Split order and put it in a stack
            this->_orderStack.clear();
            for (int idx = 0; idx < oData.PizzaNumber; ++idx)
                this->_orderStack.push_back({
                    oData.Type, oData.Size,
                    1, // Splitting order
                    oData.CookTime, oData.ID
                });
        }
        this->_data = {InstructionType::NewOrder, oData};
        while (!this->_orderStack.empty()) {
            full = true;
            auto minKitchen = this->_kitchens.begin();
            for (auto elem = _kitchens.begin(); elem != _kitchens.end(); ++elem)
                if (elem->second < minKitchen->second)
                    minKitchen = elem; // getting kitchen with the less current orders
            // std::cout << "Kitchen " << minKitchen->first << " is at " \
            //    << this->_kitchens.at(minKitchen->first) << std::endl;
            if (minKitchen->second < (this->_cooksPerKitchen * 2)) {
                this->sendData(this->_data, minKitchen->first);
                minKitchen->second += 1;
                this->_orderStack.pop_back();
                full = false;
            }
            if (full)
                this->createKitchen();
        }
        this->_currentOrders.push_back(Order(oData));
    }

    // Return true if a client was added during execution, false otherwise
    const bool DataCenter::interpretData(const SendData_t &d)
    {
        switch (d._i_type) {
            case (InstructionType::NewOrder):
                this->dealOrders(d._o_data); return (true);
            case (InstructionType::Status):
                this->displayOrders(); break;
            case (InstructionType::CloseServer):
                this->closeServer(); break;
            case (InstructionType::OrderCooked):
                this->updateCurrentOrders(d._o_data);
            default: break;
        }
        return (false);
    }
}