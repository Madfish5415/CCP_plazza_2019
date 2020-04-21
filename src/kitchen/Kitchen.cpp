/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

kitchen::Kitchen::Kitchen(uint maxCooks, uint maxPizzasPerCook)
{
    for (uint i = 0; i < maxCooks; ++i)
        this->_cooks.emplace_back(*this, maxPizzasPerCook);
}

kitchen::Kitchen::~Kitchen() = default;

kitchen::Storage& kitchen::Kitchen::getStorage() const
{
    return const_cast<Storage&>(this->_storage);
}

bool kitchen::Kitchen::handle(const pizza::IPizza::pointer& pizza)
{
    for (auto& cook : _cooks)
        if (cook.getState() == CookState::Waiting)
            if (cook.handle(pizza))
                return true;

    for (auto& cook : _cooks)
        if (cook.getState() == CookState::Cooking)
            if (cook.handle(pizza))
                return true;

    return false;
}
