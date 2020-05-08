/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <pizza/Ingredients.hpp>
#include <reception/Reception.hpp>

#include "kitchen/Settings.hpp"
#include "pizza/Recipes.hpp"
#include "pizza/Sizes.hpp"

#include "Print.hpp"

int main()
{
    pizza::Recipes::load("./data/recipes.txt");
    pizza::Sizes::load("./data/sizes.txt");

    kitchen::Settings settings {.cooks = 2, .maxPerCook = 2, .fillInterval = 1, .timeMultiplier = 1};
    std::map<std::string, unsigned int> ingredients;

    for (const auto& ingredient : pizza::Ingredients::get())
        ingredients.emplace(ingredient, 5);

    reception::Manager manager(settings, ingredients);

    int orderID = 1;
    pizza::Recipe recipe1("recipe1", {{"item1", 1}, {"item2", 1}}, 1);
    pizza::Recipe recipe2("recipe2", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Pizza pizza1(recipe1, "M", orderID);
    pizza::Pizza pizza2(recipe2, "XL", orderID);
    reception::Order order;

    order.id = orderID;
    order.pizzas.emplace_back(pizza1);
    order.pizzas.emplace_back(pizza2);

    thread::Print() << "=== Starting program ===" << std::endl;
    manager.status();
    manager.handle(order);
    manager.status();
}
