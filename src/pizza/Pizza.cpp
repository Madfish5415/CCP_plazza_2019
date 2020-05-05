/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Pizza.cpp
*/

#include "Pizza.hpp"

#include <regex>

pizza::Pizza::Pizza() = default;

pizza::Pizza::Pizza(pizza::Recipe recipe, std::string size) : _recipe(recipe), _size(size)
{
}

pizza::Pizza::~Pizza() = default;

const pizza::Recipe& pizza::Pizza::getRecipe() const
{
    return this->_recipe;
}

std::string pizza::Pizza::getSize() const
{
    return this->_size;
}

std::string pizza::Pizza::pack() const
{
    std::string string;

    string += "recipe={" + this->_recipe.pack() + "};";
    string += "size=\"" + this->_size + "\";";

    return string;
}

void pizza::Pizza::unpack(const std::string& pack)
{
    std::regex recipe("recipe=\\{(.*?)\\};");
    std::regex size("size=\"(.*?)\";");
    std::smatch match;

    if (std::regex_search(pack, match, recipe))
        this->_recipe.unpack(match.str(1));
    if (std::regex_search(pack, match, size))
        this->_size = match.str(1);
}
