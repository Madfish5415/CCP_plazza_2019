/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Storage.cpp
*/

#include "Storage.hpp"

kitchen::Storage::Storage() = default;

kitchen::Storage::~Storage() = default;

void kitchen::Storage::addIngredients(const std::map<std::string, int>& ingredients)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients)
        this->_ingredients[ingredient.first] += ingredient.second;
}

bool kitchen::Storage::hasIngredients(const std::map<std::string, int>& ingredients)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            return false;

        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            return false;
    }

    return true;
}

void kitchen::Storage::removeIngredients(const std::map<std::string, int>& ingredients)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            throw std::exception(); // TODO: Custom Error class

        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            throw std::exception(); // TODO: Custom Error class

        this->_ingredients[ingredient.first] -= ingredient.second;
    }
}
