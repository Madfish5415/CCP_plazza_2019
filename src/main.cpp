/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include "process/Kitchen.hpp"

int main()
{
    auto *k = new process::Kitchen(2, {{"doe", 10}, {"cheese", 5}});
    pizza::Recipe margarita("Margarita", {{"doe", 1}, {"cheese", 1}}, 5);
    pizza::Pizza p1(margarita, "10");
    pizza::Pizza p2(margarita, "10");

    k->send(p1);
    k->send(p2);
    k->status();

    delete k;

    return 0;
}
