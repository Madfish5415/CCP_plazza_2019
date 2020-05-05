/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include "process/Kitchen.hpp"

int main()
{
    process::Kitchen processKitchen(
        2, {{"item1", 30}, {"item2", 25}, {"item3", 20}, {"item4", 15}, {"item5", 10}, {"item6", 5}});
    pizza::Recipe recipe1("recipe1", {{"item1", 1}, {"item2", 1}}, 1);
    pizza::Recipe recipe2("recipe2", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe3("recipe3", {{"item5", 1}, {"item6", 1}}, 1);
    pizza::Pizza pizza1(recipe1, "M");
    pizza::Pizza pizza2(recipe2, "M");
    pizza::Pizza pizza3(recipe3, "M");

    processKitchen.status();
    processKitchen.send(pizza1);
    processKitchen.send(pizza2);
    processKitchen.status();
    processKitchen.send(pizza3);
    processKitchen.run();

    return 0;
}
