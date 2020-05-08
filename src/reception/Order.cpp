/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Order.cpp
*/

#include "Order.hpp"

#include <thread/Print.hpp>

reception::Order::Order() = default;

reception::Order::~Order() = default;

void reception::Order::display() const
{
    thread::Print print;

    print << "Order n°" << this->id << ":" << std::endl;

    for (const auto& pizza : this->pizzas)
        print << "- " << pizza->getRecipe().getType() << std::endl;
}
