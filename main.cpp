/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main
*/

#include "Thread.hpp"

void test(int x, int y)
{
    std::cout << "Ceci est un test: " << x << " " << y << std::endl;
}

int main(void)
{
    Plazza::Thread<void> thread(test, 10, 10);

    thread.Wait();
    return 0;
}