/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Recipe.cpp
*/

#include "Recipe.hpp"

#include <regex>

pizza::Recipe::Recipe()
{
}

pizza::Recipe::Recipe(
    const std::string& _type, const std::map<std::string, unsigned int>& ingredients, unsigned int cookTime)
{
}

pizza::Recipe::~Recipe()
{
}

std::string pizza::Recipe::getType() const
{
    return this->_type;
}

const std::map<std::string, unsigned int>& pizza::Recipe::getIngredients() const
{
    return this->_ingredients;
}

unsigned int pizza::Recipe::getCookTime() const
{
    return this->_cookTime;
}

std::string pizza::Recipe::pack() const
{
    std::string string;

    string += "type=\"" + this->_type + "\";";
    string += "ingredients=";

    for (const auto& ingredient : this->_ingredients) {
        if (ingredient != *this->_ingredients.begin())
            string += ",";
        string += "\"" + ingredient.first + "\":" + std::to_string(ingredient.second);
    }

    string += ";";
    string += "cookTime=" + std::to_string(this->_cookTime) + ";";

    return string;
}

void pizza::Recipe::unpack(const std::string& pack)
{
    std::regex type("type=\"(.*?)\";");
    std::regex ingredients("ingredients=(.*?);");
    std::regex ingredient("\"([^:]+)\":(\\d+)");
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
