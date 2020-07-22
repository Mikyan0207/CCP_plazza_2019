/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include <Kitchen.hpp>

namespace Plazza
{
    Kitchen::Kitchen(const uint& reloadTimeMS, const uint &cpk)
    {
        this->_stock = std::make_unique<FoodStock>(reloadTimeMS);
        this->_pool = std::make_unique<ThreadPool>(cpk, this->_stock.get());
        this->_lastActivity = std::chrono::duration_cast<std::chrono::seconds> \
            (std::chrono::_V2::system_clock::now().time_since_epoch());
    }

    Kitchen::~Kitchen()
    {
        if (this->_cli.getSockDescr() != (-1)) {
            OrderData d;
            d.ID = getpid();
            this->_cli.sendData({InstructionType::K_closing, d});
        }
    }

    void Kitchen::connectToDataCenter(void)
    {
        this->_cli = Client(refFile);
        this->_cli.connectToServer();
        this->_cli.updateFDSet();
    }

    void Kitchen::Run()
    {
        connectToDataCenter();
        ProcessOrders();
    }

    const Pizza Kitchen::GetPizza(const OrderData &order)
    {
        switch (order.Type) {
            case PizzaType::Regina:
                return Regina(order);
            case PizzaType::Fantasia:
                return Fantasia(order);
            case PizzaType::Margarita:
                return Margarita(order);
            case PizzaType::Americana:
                return Americana(order);
            default:
                throw Exception("Invalid Pizza type");
        }
    }

    void Kitchen::checkUp(void)
    {
        SendData_t tmp;
        fd_set tmp_fdset;
        timeval to = {0, 1000};

        FD_ZERO(&(tmp_fdset));
        FD_SET(this->_cli.getSockDescr(), &(tmp_fdset));
        if (select(this->_cli.getSockDescr() + 1, &(tmp_fdset), NULL, NULL, &to) < 0)
            std::cerr << "select error" << std::endl;
        if (FD_ISSET(this->_cli.getSockDescr(), &(tmp_fdset))) {
            if ((read(this->_cli.getSockDescr(), &tmp, sizeof(SendData_t))) == 0) {
                this->_cli.closeSocketDescr();
                this->_open = false;
                return;
            } else
                this->interpretData(tmp);
        }
    }

    void Kitchen::sendStatus(void)
    {
        std::stringstream ss;

        ss << "\e[36m-- Cooks --\e[39m" << std::endl;

        int i = 1;
        for (auto &thread : this->_pool->GetThreads()) {
            ss << "Cook #" << i << ": "
               << (thread.IsActive() ? "\e[31mWorking\e[39m" : "\e[32mWaiting\e[39m")
               << std::endl;
            i += 1;
        }

        ss << std::endl << "\e[36m-- Ingredients Sock --\e[39m" << std::endl;
        for (auto& item : this->_stock->getStockStatus()) {
            ss << "\e[35m" << item.first << "\e[39m -> ";

            if (item.second <= 1)
                ss << "\e[91m" << item.second;
            else if (item.second <= 3)
                ss << "\e[33m" << item.second;
            else
                ss << "\e[32m" << item.second;

            ss << "\e[39m"<< "" << std::endl;
        }

        std::cout << ss.str();
        ss.clear();

        // for (auto &item : this->_pool->GetPendingTasks().GetQueue())
        //     std::cout << item.ToString() << std::endl;
    }

    void Kitchen::sendAvailableness(void)
    {
        SendData_t tmp {InstructionType::K_Availableness, OrderData()};
        int cookso = 0;

        tmp._o_data.PizzaNumber = 0;
        for (auto &item : this->_pool->GetThreads()) {
            if (item.IsActive())
                cookso += 1;
        }

        tmp._o_data.PizzaNumber = cookso + this->_pool->TasksCount();
        // std::cout << "\nCooks cooking  ->\t" << cookso << std::endl;
        // std::cout << "Orders pending ->\t" << this->_pool->TasksCount() << std::endl;
        // std::cout << "Total occupation ->\t" << tmp._o_data.PizzaNumber << std::endl;
        this->_cli.sendData(tmp);
    }

    void Kitchen::interpretData(const SendData_t &d)
    {
        switch (d._i_type) {
            case (InstructionType::NewOrder):
                this->_pool->AddTask(this->GetPizza(d._o_data)); break;
            case (InstructionType::CloseKitchen):
                this->_cli.closeSocketDescr();
                this->_open = false; break;
            case (InstructionType::Status):
                this->sendStatus();
            default: break;
        }
    }

    void Kitchen::SendCookedPizza()
    {
        while (!this->_pool->GetTasksDone().IsEmpty()) {
            Pizza pizza = this->_pool->GetTasksDone().Pop();
            // Send data to server
            this->_cli.sendData({
                InstructionType::OrderCooked,
                OrderData(pizza)
            });
            this->sendAvailableness();
        }
    }

    void Kitchen::AutoClose()
    {
        while (_open) {
            bool isActive = false;

            if (!this->_pool->GetPendingTasks().IsEmpty())
                isActive = true;
            
            if (!isActive) {
                for (auto& item : this->_pool->GetThreads()) {
                    if (item.IsActive()) {
                        isActive = true;
                        break;
                    }
                }
            }

            if (isActive) {
                _lastActivity = std::chrono::duration_cast<std::chrono::seconds> \
                (std::chrono::_V2::system_clock::now().time_since_epoch());
            }

            auto now = std::chrono::duration_cast<std::chrono::seconds>\
            (std::chrono::_V2::system_clock::now().time_since_epoch());

            if (now.count() - _lastActivity.count() > std::chrono::seconds(5).count()) {
                _open = false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Kitchen::ProcessOrders(void)
    {
        Thread stockThread;
        Thread autoCloseThread;

        stockThread.Run([this]() {
            // @Info: Check if we can refill stock
            while (this->_open) {
                this->_stock->update();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });

        autoCloseThread.Run(&Kitchen::AutoClose, this);

        this->_pool->StartAll(); // Init Thread class
        this->_pool->ExecuteTasks(); // Start Workers

        while (this->_open) {
            this->checkUp();
            this->SendCookedPizza();
        }
    }
}