/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main
*/

#include "Thread.hpp"

void test(int x, int y)
{
    std::cout << x << " + " << y << " = " << x + y << std::endl;
}

int main(void)
{
    Plazza::Thread thread(test, 10, 10);

    if (thread.Joinable())
        thread.Wait();

    if (thread.Joinable())
        std::cout << "Running" << std::endl;
    else
        std::cout << "Dead" << std::endl;
    return 0;
}