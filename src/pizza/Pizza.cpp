/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Pizza.cpp
*/

#include "Pizza.hpp"

#include <regex>
#include <utility>

pizza::Pizza::Pizza() = default;

pizza::Pizza::Pizza(const pizza::Recipe& recipe, std::string size, unsigned int order)
    : _recipe(recipe), _size(std::move(size)), _order(order)
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

unsigned int pizza::Pizza::getOrder() const
{
    return this->_order;
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
