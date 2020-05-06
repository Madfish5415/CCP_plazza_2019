/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** stress_test
*/

// #include <string.c>
#include "process/Kitchen.hpp"
#include "reception/Manager.hpp"

int main(int argc, char **argv)
{
    reception::Manager manager(
        2, {{"item1", 30}, {"item2", 25}, {"item3", 20}, {"item4", 15}, {"item5", 10}, {"item6", 5}});
    /*process::Kitchen kitchen(
        2, {{"item1", 30}, {"item2", 25}, {"item3", 20}, {"item4", 15}, {"item5", 10}, {"item6", 5}}, "/mario", "/luigi"); */
    pizza::Recipe recipe1("recipe1", {{"item1", 1}, {"item2", 1}}, 1);
    pizza::Recipe recipe2("recipe2", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe3("recipe3", {{"item5", 1}, {"item6", 1}}, 1);
    pizza::Recipe recipe4("recipe4", {{"item1", 1}, {"item2", 1}}, 1);
    pizza::Recipe recipe5("recipe5", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe6("recipe6", {{"item5", 1}, {"item6", 1}}, 1);
    std::vector<pizza::Pizza> pizzaList = {pizza::Pizza(recipe1, "M"), pizza::Pizza(recipe2, "M"), pizza::Pizza(recipe3, "M"), pizza::Pizza(recipe4, "M"), pizza::Pizza(recipe5, "M"), pizza::Pizza(recipe6, "M")};

    for (int i = 0; argc != 1 && i < atoi(argv[1]); i++) {
        manager.handle(pizzaList[rand() % 6]);
    }
    manager.status();
    manager.manage();

    return 0;
}
