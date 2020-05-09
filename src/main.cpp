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
        ingredients.emplace(ingredient, 100);

    reception::Manager manager(settings, ingredients);

    reception::Order order;
    pizza::Recipe recipe1("recipe1", {{"item1", 1}, {"item2", 1}}, 1);
    pizza::Recipe recipe2("recipe2", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe3("recipe3", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe4("recipe4", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe5("recipe5", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe6("recipe6", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe7("recipe7", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe8("recipe8", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe9("recipe9", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Recipe recipe10("recipe10", {{"item3", 1}, {"item4", 1}}, 1);
    pizza::Pizza pizza1(recipe1, "M", order.getId());
    pizza::Pizza pizza2(recipe2, "XL", order.getId());
    pizza::Pizza pizza3(recipe3, "M", order.getId());
    pizza::Pizza pizza4(recipe4, "XL", order.getId());
    pizza::Pizza pizza5(recipe5, "M", order.getId());
    pizza::Pizza pizza6(recipe6, "XL", order.getId());
    pizza::Pizza pizza7(recipe7, "M", order.getId());
    pizza::Pizza pizza8(recipe8, "XL", order.getId());
    pizza::Pizza pizza9(recipe9, "M", order.getId());
    pizza::Pizza pizza10(recipe10, "XL", order.getId());

    order.add(pizza1);
    order.add(pizza2);
    order.add(pizza3);
    order.add(pizza4);
    order.add(pizza5);
    order.add(pizza6);
    order.add(pizza7);
    order.add(pizza8);
    order.add(pizza9);
    order.add(pizza10);

    manager.handle(order);
    manager.status();
}
