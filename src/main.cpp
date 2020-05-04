/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include "process/Kitchen.hpp"

int main()
{
    process::Kitchen k(2, {{"doe", 10}, {"cheese", 5}});
    pizza::Recipe margarita("Margarita", {{"doe", 1}, {"cheese", 1}}, 1);
    pizza::Pizza p(margarita, "M");

    k.status();
    k.send(p);
    k.send(p);
    k.status();
    k.send(p);

    return 0;
}
