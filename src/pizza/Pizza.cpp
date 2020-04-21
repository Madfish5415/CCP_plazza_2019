/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Pizza.cpp
*/

#include "Pizza.hpp"

#include <sstream>
#include <vector>

static std::vector<std::string> split(
    const std::string& str, const std::string& delim)
{
    std::vector<std::string> v;

    std::size_t current = str.find(delim);
    std::size_t previous = 0;

    for (; current != std::string::npos;
         previous = current + 1, current = str.find(delim, previous)) {
        v.emplace_back(str.substr(previous, current - previous));
    }

    v.emplace_back(str.substr(previous, current - previous));

    return v;
}

pizza::Pizza::Pizza(pizza::PizzaType type,
    const pizza::IPizza::Ingredients& ingredients, pizza::PizzaSize size,
    pizza::IPizza::CookTime cookTime)
    : _type(type), _ingredients(ingredients), _size(size), _cookTime(cookTime)
{
}

pizza::Pizza::~Pizza() = default;

pizza::IPizza::CookTime pizza::Pizza::getCookTime() const
{
    return this->_cookTime;
}

const pizza::IPizza::Ingredients& pizza::Pizza::getIngredients() const
{
    return this->_ingredients;
}

pizza::PizzaSize pizza::Pizza::getSize() const
{
    return this->_size;
}

pizza::PizzaType pizza::Pizza::getType() const
{
    return this->_type;
}

std::string pizza::Pizza::pack() const
{
    std::stringstream string;

    string << "type=" << this->_type << ";";
    string << "ingredients=";

    for (const auto& ingredient : _ingredients) {
        if (&ingredient != &*_ingredients.begin())
            string << ",";
        string << ingredient.first << ":" << ingredient.second;
    }

    string << ";";
    string << "size=" << this->_size << ";";
    string << "cookTime=" << this->_cookTime.count();

    return string.str();
}

void pizza::Pizza::unpack(const std::string& pack)
{
    const auto& properties = split(pack, ";");

    for (const auto& property : properties) {
        const auto& typeAndValue = split(property, "=");

        if (typeAndValue[0] == "type")
            this->_type = static_cast<PizzaType>(std::stoi(typeAndValue[1]));
        if (typeAndValue[0] == "size")
            this->_size = static_cast<PizzaSize>(std::stoi(typeAndValue[1]));
        if (typeAndValue[0] == "cookTime")
            this->_cookTime = std::chrono::seconds(std::stoi(typeAndValue[1]));
        if (typeAndValue[0] == "ingredients") {
            const auto& ingredients = split(typeAndValue[1], ",");

            for (const auto& ingredient : ingredients) {
                const auto& nameAndValue = split(ingredient, ":");

                this->_ingredients[nameAndValue[0]] =
                    std::stoi(nameAndValue[1]);
            }
        }
    }
}
