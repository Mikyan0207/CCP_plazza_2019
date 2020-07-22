/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main
*/

#include <DataCenter.hpp>
#include <IPC/Server.hpp>
#include <Process/Process.hpp>
#include <Reception.hpp>
#include <Exceptions/Exception.hpp>

int main(int ac, char **av)
{
    Plazza::Reception r;

    try {
        if (ac != 4)
            throw (Plazza::InitException("Invalid number of argument."));
        r.setArgumentsFromTab(av + 1);
        Plazza::DataCenter server(r.getIngredientreplaceTime(), r.getCooksNbPerKitchen());
        Plazza::Process rProcess(r);
        server.manageData();
    } catch (Plazza::InitException &e) {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    } catch (Plazza::SocketException &e) {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    } catch (Plazza::ServerException &e) {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    } catch (Plazza::Exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    }
    return (0);
}