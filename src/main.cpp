/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include "process/Kitchen.hpp"
#include "reception/Manager.hpp"

int main()
{
    reception::Manager manager(
        2, {{"item1", 30}, {"item2", 25}, {"item3", 20}, {"item4", 15}, {"item5", 10}, {"item6", 5}});
    pizza::Recipe recipe1("recipe1", {{"item1", 1}, {"item2", 1}}, 1);
    pizza::Recipe recipe2("recipe2", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe3("recipe3", {{"item5", 1}, {"item6", 1}}, 1);
    pizza::Recipe recipe4("recipe4", {{"item1", 1}, {"item2", 1}}, 1);
    pizza::Recipe recipe5("recipe5", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe6("recipe6", {{"item5", 1}, {"item6", 1}}, 1);
    pizza::Pizza pizza1(recipe1, "M");
    pizza::Pizza pizza2(recipe2, "M");
    pizza::Pizza pizza3(recipe3, "M");
    pizza::Pizza pizza4(recipe4, "M");
    pizza::Pizza pizza5(recipe5, "M");
    pizza::Pizza pizza6(recipe6, "M");

    manager.status();
    manager.handle(pizza1);
    manager.handle(pizza2);
    manager.status();
    manager.handle(pizza3);
    manager.handle(pizza4);
    manager.handle(pizza5);
    manager.handle(pizza6);
    manager.status();
    manager.manage();

    return 0;
}
