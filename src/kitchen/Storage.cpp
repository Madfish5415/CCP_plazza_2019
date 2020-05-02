/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Storage.cpp
*/

#include "Storage.hpp"

#include <iostream>

kitchen::Storage::Storage(const std::map<std::string, unsigned int>& ingredients) : _ingredients(ingredients)
{
}

kitchen::Storage::~Storage() = default;

void kitchen::Storage::addIngredients(const std::map<std::string, unsigned int>& ingredients)
{
    for (const auto& ingredient : ingredients)
        this->_ingredients[ingredient.first] += ingredient.second;
}

bool kitchen::Storage::hasIngredients(const std::map<std::string, unsigned int>& ingredients) const
{
    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            return false;
        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            return false;
    }

    return true;
}

void kitchen::Storage::removeIngredients(const std::map<std::string, unsigned int>& ingredients)
{
    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            throw std::exception(); // TODO: Custom Error class
        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            throw std::exception(); // TODO: Custom Error class

        this->_ingredients[ingredient.first] -= ingredient.second;
    }
}

void kitchen::Storage::status() const
{
    for (const auto& ingredient : this->_ingredients)
        std::cout << "- " << ingredient.first << " x" << ingredient.second << std::endl;
}
