/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#include "Cook.hpp"

#include <iostream>

#include "../def/def.hpp"
#include "Kitchen.hpp"

kitchen::Cook::Cook(kitchen::Kitchen& kitchen) : _kitchen(kitchen), _state(State::Working), _thread(&Cook::cook, this)
{
}

kitchen::Cook::~Cook()
{
    this->_state = State::Finished;

    std::cout << std::this_thread::get_id() << " Cook::~Cook()" << std::endl; // TODO: Remove

    this->_thread.join();
}

const std::queue<pizza::Pizza>& kitchen::Cook::getPizzas() const
{
    return this->_pizzas;
}

void kitchen::Cook::cook()
{
    std::cout << std::this_thread::get_id() << " start cooking" << std::endl; // TODO: Remove

    while ((this->_state == State::Working) || !this->_pizzas.empty()) {
        if (this->_pizzas.empty())
            continue;

        auto& pizza = this->_pizzas.front();
        auto& storage = this->_kitchen.getStorage();

        if (!storage.hasIngredients(pizza.getRecipe().getIngredients()))
            continue;

        storage.removeIngredients(pizza.getRecipe().getIngredients());

        std::this_thread::sleep_for(std::chrono::seconds(pizza.getRecipe().getCookTime()));

        this->_pizzas.pop();
        // this->ready(pizza); // TODO: FIX THIS SHIT

        std::cout << std::this_thread::get_id() << " finished a " << pizza.getRecipe().getType() << std::endl; // TODO: Remove
        std::cout << std::this_thread::get_id() << "'s pizza queue size: " << this->_pizzas.size() << std::endl; // TODO: Remove
    }

    std::cout << std::this_thread::get_id() << " end cooking" << std::endl; // TODO: Remove
}

bool kitchen::Cook::handle(const pizza::Pizza& pizza)
{
    if (this->_state != State::Working)
        return false;
    if (this->_pizzas.size() >= MAX_PIZZAS)
        return false;

    this->_pizzas.push(pizza);

    return true;
}

void kitchen::Cook::ready(const pizza::Pizza& pizza)
{
    this->_kitchen.ready(pizza);
}

void kitchen::Cook::status() const
{
    std::cout << "Cook n°" << this->_thread.get_id() << ":" << std::endl;
    std::cout << "Action: ";

    if (this->_pizzas.empty()) {
        std::cout << "Waiting for a pizza";
    } else {
        auto& pizza = this->_pizzas.front();

        std::cout << "Cooking a(n) " << pizza.getSize() << " " << pizza.getRecipe().getType();
    }

    std::cout << std::endl;
}

void kitchen::Cook::wait()
{
    this->_thread.join();
}
