/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

kitchen::Kitchen::Kitchen(int cooks, int maxPizzasPerCook) : _process(&Kitchen::cook, this)
{
    for (int i = 0; i < cooks; ++i)
        this->_cooks.emplace_back(*this, maxPizzasPerCook);
}

kitchen::Kitchen::~Kitchen() = default;

kitchen::KitchenState kitchen::Kitchen::getState() const
{
    return this->_state;
}

kitchen::Storage& kitchen::Kitchen::getStorage() const
{
    return const_cast<Storage&>(this->_storage);
}
