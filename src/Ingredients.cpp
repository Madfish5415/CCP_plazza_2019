/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredients.cpp
*/

#include "Ingredients.hpp"

#include <regex>

void Ingredients::add(const std::string& ingredient)
{
    Ingredients::ingredients().emplace(ingredient);
}

bool Ingredients::has(const std::string& ingredient)
{
    return Ingredients::ingredients().count(ingredient);
}

std::set<std::string>& Ingredients::get()
{
    return Ingredients::ingredients();
}

std::set<std::string>& Ingredients::ingredients()
{
    static std::set<std::string> ingredients;

    return ingredients;
}