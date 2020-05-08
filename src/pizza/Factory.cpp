/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Factory.cpp
*/

#include "Factory.hpp"

#include "Recipes.hpp"
#include "Sizes.hpp"

std::shared_ptr<pizza::Pizza> pizza::Factory::create(
    const std::string& recipe, const std::string& size, unsigned int order)
{
    auto pizza = std::make_shared<pizza::Pizza>(Recipes::get().at(recipe), *Sizes::get().find(size), order);

    return pizza;
}
