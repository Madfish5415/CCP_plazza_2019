/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <pizza/Factory.hpp>
#include <pizza/Ingredients.hpp>
#include <pizza/Recipes.hpp>
#include <pizza/Sizes.hpp>
#include <reception/Manager.hpp>

int main()
{
    pizza::Recipes::load("./data/recipes.txt");
    pizza::Sizes::load("./data/sizes.txt");

    kitchen::Settings settings {
        .timeMultiplier = 0.75,
        .cooks = 2,
        .refillInterval = 1000,
        .maxPerCook = MAX_PER_COOK,
        .maxWaiting = MAX_WAITING
    };
    std::map<std::string, unsigned int> ingredients;

    for (const auto& ingredient : pizza::Ingredients::get())
        ingredients.emplace(ingredient, MAX_INGREDIENT_UNIT);

    reception::Manager manager(settings, ingredients);

    reception::Order order;

    auto regina = pizza::Factory::create("regina", "XL", order.getId());

    order.add(regina);

    manager.status();
    manager.handle(order);
    manager.status();
    process::This::sleepFor(std::chrono::seconds(1));
    manager.status();
    process::This::sleepFor(std::chrono::seconds(1));
    manager.status();
}
