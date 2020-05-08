/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Ingredients.cpp
*/

#include "Ingredients.hpp"

std::set<std::string>& pizza::Ingredients::_ingredients()
{
    static std::set<std::string> ingredients;

    return ingredients;
}

std::set<std::string>& pizza::Ingredients::get()
{
    return Ingredients::_ingredients();
}
