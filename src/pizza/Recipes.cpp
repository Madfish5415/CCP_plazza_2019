/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Recipes.cpp
*/

#include "Recipes.hpp"

#include <fstream>

#include "Ingredients.hpp"

std::map<std::string, pizza::Recipe>& pizza::Recipes::get()
{
    return Recipes::_recipes;
}

void pizza::Recipes::load(const std::string& path)
{
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        Recipe recipe;

        recipe.unpack(line);

        Recipes::_recipes.emplace(recipe.getType(), recipe);

        for (const auto& ingredient : recipe.getIngredients())
            Ingredients::get().emplace(ingredient.first);
    }
}
