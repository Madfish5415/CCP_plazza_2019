/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Pizza.cpp
*/

#include "Pizza.hpp"

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
    return std::string();
}

void pizza::Pizza::unpack(const std::string& pack) const
{
    (void)(pack);
}
