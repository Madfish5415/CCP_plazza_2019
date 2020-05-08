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

int main()
{
    pizza::Recipes::load("./data/recipes.txt");
    pizza::Sizes::load("./data/sizes.txt");

    kitchen::Settings settings {.cooks = 2, .maxPerCook = 2, .fillInterval = 1, .timeMultiplier = 1};
    std::map<std::string, unsigned int> ingredients;

    for (const auto& ingredient : pizza::Ingredients::get())
        ingredients.emplace(ingredient, 5);

    reception::Reception r(settings, ingredients);

    r.run();
}
