/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Factory.cpp
*/

#include "Factory.hpp"

#include "Recipes.hpp"
#include "Sizes.hpp"

pizza::Pizza pizza::Factory::create(const std::string& recipe, const std::string& size, unsigned int order)
{
    auto recipeObj = Recipes::get().at(recipe);

    if (Sizes::get().count(size) == 0)
        throw std::exception(); // TODO: Custom Error class

    pizza::Pizza pizza(recipeObj, size, order);

    return pizza;
}
