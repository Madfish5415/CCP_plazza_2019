/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <pizza/Ingredients.hpp>
#include <pizza/Recipes.hpp>
#include <pizza/Sizes.hpp>
#include <reception/Manager.hpp>
#include <reception/Reception.hpp>

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

    reception::Reception reception(settings, ingredients);

    reception.run();
}
