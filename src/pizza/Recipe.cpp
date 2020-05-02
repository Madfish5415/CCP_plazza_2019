/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Recipe.cpp
*/

#include "Recipe.hpp"

#include <regex>
#include <sstream>

pizza::Recipe::Recipe() : _cookTime(0)
{
}

pizza::Recipe::Recipe(const std::string& type, const std::map<std::string, unsigned int>& ingredients, int cookTime)
    : _type(type), _ingredients(ingredients), _cookTime(cookTime)
{
}

pizza::Recipe::~Recipe() = default;

std::string pizza::Recipe::getType() const
{
    return this->_type;
}

const std::map<std::string, unsigned int>& pizza::Recipe::getIngredients() const
{
    return this->_ingredients;
}

int pizza::Recipe::getCookTime() const
{
    return this->_cookTime;
}

std::string pizza::Recipe::pack() const
{
    std::stringstream string;

    string << "type=" << this->_type << ";";
    string << "ingredients=";

    for (const auto& ingredient : this->_ingredients) {
        if (ingredient != *this->_ingredients.begin())
            string << ",";
        string << ingredient.first << ":" << ingredient.second;
    }

    string << ";";
    string << "cookTime=" << this->_cookTime << ";";

    return string.str();
}

void pizza::Recipe::unpack(const std::string& pack)
{
    std::regex type("type=(.*?);");
    std::regex ingredients("ingredients=(.*?);");
    std::regex ingredient("([a-z]+):(\\d+)");
    std::regex cookTime("cookTime=(.*?);");
    std::smatch match;

    if (std::regex_search(pack, match, type))
        this->_type = match.str(1);
    if (std::regex_search(pack, match, ingredients)) {
        std::string find = match.str(1);

        while (std::regex_search(find, match, ingredient)) {
            this->_ingredients[match.str(1)] = std::stoi(match.str(2));

            find = match.suffix();
        }
    }
    if (std::regex_search(pack, match, cookTime))
        this->_cookTime = std::stoi(match.str(1));
}
