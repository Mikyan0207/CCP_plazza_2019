/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#include <Reception.hpp>

namespace Plazza
{
    Reception::Reception()
    {
        this->initMaps();
        this->_logFile.open("record.txt", std::ios_base::app);
        if (this->_logFile.bad() || this->_logFile.fail())
            throw Exception("Faild to open file.");
    }

    Reception::Reception(const float &cookingTMult, \
    const int &cooksPerKitchen, const double &replaceTime) :
    _cookingTimeMultiplier(cookingTMult),
    _cooksPerKitchen(cooksPerKitchen),
    _replaceTimeMS(replaceTime)
    {
        this->initMaps();
    }

    void Reception::initMaps(void)
    {
        this->_cookingTimeMapMS = {
            std::make_pair(PizzaType::Regina,    2000),
            std::make_pair(PizzaType::Margarita, 1000),
            std::make_pair(PizzaType::Americana, 2000),
            std::make_pair(PizzaType::Fantasia,  4000),
        };
        this->_sData._o_data = OrderData();
    }

    void Reception::connectToDataCenter()
    {
        this->_cli = Client(refFile);
        this->_cli.connectToServer();
    }

    void Reception::Run()
    {
        connectToDataCenter();
        loop();
    }

    /////////////////////////// SETTERS ///////////////////////////

    void Reception::setCookingTimeMultiplier(const float &ctm)
    {
        if (ctm < 0)
            throw (InitException("A time multiplier cannot be a negative number."));
        this->_cookingTimeMultiplier = ctm;
    }

    void Reception::setCooksNbPerKitchen(const int &cpk)
    {
        if (cpk <= 0)
            throw (InitException("There must be at least one cook per kitchen."));
        this->_cooksPerKitchen = cpk;
    }

    void Reception::setIngredientreplaceTime(const double &irt)
    {
        if (irt < 0)
            throw (InitException("Sorry humans cannot go back in time... for now."));
        this->_replaceTimeMS = irt;
    }

    void Reception::setArgumentsFromTab(char **av)
    {
        this->setCookingTimeMultiplier(std::stof(std::string(av[0])));
        this->setCooksNbPerKitchen(std::stoi(std::string(av[1])));
        this->setIngredientreplaceTime(std::stod(std::string(av[2])));
    }

    ///////////////////////////////////////////////////////////////

    const std::string &Reception::clearString(std::string &str)
    {
        while (str[0] == ' ' || str[0] == '\t')
            str = str.substr(1);
        while (str[str.length() - 1] == ' ' || \
        str[str.length() - 1] == '\t')
            str = str.substr(0, str.length() - 1);
        return (str);
    }

    void Reception::storeOrder(const std::string &str)
    {
        OrderData nOrder;
        std::stringstream sorder(str);
        std::vector<std::string> tab;

        while (std::getline(sorder, this->_input, ' '))
            if (this->_input.length() > 0)
                tab.push_back(this->_input);
        try {
            if (tab.size() != 3)
                throw (OrderException("Missing parameter(s)."));
            { // Get pizza type
                std::transform(tab[0].begin(), tab[0].end(), tab[0].begin(),
                               [](unsigned char c) { return (std::tolower(c)); });
                for (const auto elem : Plazza::PizzaTypeMap) {
                    if (elem.second.compare(tab[0]) == 0)
                        nOrder.Type = elem.first;
                }
                if (nOrder.Type == PizzaType::Undefined)
                    throw (OrderException("Unknown pizza was ordered."));
            } { // Get Pizza Size
                std::transform(tab[1].begin(), tab[1].end(), tab[1].begin(),
                               [](unsigned char c) { return (std::toupper(c)); });
                for (const auto elem : Plazza::PizzaSizeMap) {
                    if (elem.second.compare(tab[1]) == 0)
                        nOrder.Size = elem.first;
                }
                if (nOrder.Size == PizzaSize::U)
                    throw (OrderException("Unknown pizza size."));
            } { // Get number of pizzas
                if ((tab[2][0] != 'x' && tab[2][0] != 'X') || \
                std::stoi(tab[2].substr(1)) <= 0)
                    throw (OrderException("Wrong syntax."));
                nOrder.PizzaNumber = std::stoi(tab[2].substr(1));
                // Set cooking time
                nOrder.CookTime = this->_cookingTimeMapMS.at(nOrder.Type) * this->_cookingTimeMultiplier;
            }
            nOrder.ID = this->_commandNb;
            this->_commandNb += 1;
            this->_orders.push_back(nOrder);
        } catch (OrderException e) {
            std::cerr << e.what() << std::endl;
            this->closePizzeria();
            std::exit(84);
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            this->closePizzeria();
            std::exit(84);
        }
    }

    void Reception::giveOrdersToKitchens(void)
    {
        for (auto &elem : this->_orders)
            this->_cli.sendData({InstructionType::NewOrder, elem});
        this->_orders.clear();
    }

    void Reception::getOrderFromCurrentInput(void)
    {
        std::string currentOrder;
        std::stringstream sstr(this->clearString(this->_input));

        while (std::getline(sstr, this->_input, ';'))
            if (this->_input.length() > 0)
                this->storeOrder((currentOrder = this->clearString(this->_input)));
    }

    const bool Reception::checkUp(void)
    {
        int tmp_maxFD;

        std::cout << "PLAZZA ~> " << std::flush;
        { // Updating fd_set for next select()
            FD_ZERO(&(this->_readfds));
            FD_SET(this->_cli.getSockDescr(), &(this->_readfds));
            FD_SET(0, &(this->_readfds)); // set input
            tmp_maxFD = this->_cli.getSockDescr();
        }
        { // Waiting for activity on previously set fds
            if (select(tmp_maxFD + 1, &(this->_readfds), NULL, NULL, NULL) < 0)
                std::cerr << "Select error" << std::endl;
        }
        { // Check for DataCenter message
            if (FD_ISSET(this->_cli.getSockDescr(), &(this->_readfds))) {
                if ((read(_cli.getSockDescr(), &(_sData), sizeof(SendData_t))) == 0) {
                    this->_cli.closeSocketDescr();
                    this->_open = false;
                } else if (this->_sData._i_type == InstructionType::OrderReady)
                    this->announceOrder(this->_sData._o_data);
            }
        }
        { // Check for new Input message
            if (FD_ISSET(0, &(this->_readfds))) {
                if (!std::getline(std::cin, this->_input)) {
                    this->_open = false;
                    return (this->_open);
                } else if (this->_input == "status") {
                    this->_sData._i_type = InstructionType::Status;
                    this->_cli.sendData(this->_sData);
                } else {
                    this->getOrderFromCurrentInput();
                    this->giveOrdersToKitchens();
                }
            }
        }
        return (this->_open);
    }

    void Reception::announceOrder(const OrderData &d)
    {
        auto t = std::chrono::system_clock::now();
        std::time_t et = std::chrono::system_clock::to_time_t(t);
        std::string tmps(std::to_string(d.PizzaNumber) + " " + \
        PizzaSizeMap.at(d.Size) + " " + PizzaTypeMap.at(d.Type) + \
        ((d.PizzaNumber > 1) ? "s" : ""));
        std::string date(std::ctime(&et));

        this->_logFile << "[" << date.substr(0, date.length() - 1) << "] - " << tmps << std::endl;
        std::cout << "\nThe order containing " << tmps << " is ready !" << std::endl;
    }

    const int Reception::loop(void)
    {
        while (this->_open && this->checkUp());
        this->closePizzeria();
        return (0);
    }

    void Reception::closePizzeria(void)
    {
        this->_sData._i_type = InstructionType::CloseServer;
        this->_cli.sendData(this->_sData);
        this->_cli.closeSocketDescr();
        this->_logFile.close();
    }
}
