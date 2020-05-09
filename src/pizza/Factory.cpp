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
    pizza::Pizza pizza(Recipes::get().at(recipe), *Sizes::get().find(size), order);

    return pizza;
}
