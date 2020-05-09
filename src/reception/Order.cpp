/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Order.cpp
*/

#include "Order.hpp"

#include <thread/Print.hpp>

reception::Order::Order() : _id(Order::id()), _ready(0)
{
}

reception::Order::~Order() = default;

unsigned int reception::Order::getId() const
{
    return this->_id;
}

const std::list<pizza::Pizza>& reception::Order::getPizzas() const
{
    return this->_pizzas;
}

unsigned int reception::Order::getPending() const
{
    return (this->_pizzas.size() - this->_ready);
}

bool reception::Order::isComplete() const
{
    return (this->_pizzas.size() == this->_ready);
}

void reception::Order::add(pizza::Pizza pizza)
{
    this->_pizzas.push_back(pizza);
}

void reception::Order::display() const
{
    thread::Print print;

    print << "Order n°" << this->_id << ":" << std::endl;

    for (const auto& pizza : this->_pizzas)
        print << "- " << pizza.getRecipe().getType() << std::endl;
}

void reception::Order::ready()
{
    this->_ready += 1;
}

unsigned int reception::Order::id()
{
    static unsigned int id = 0;

    return ++id;
}
