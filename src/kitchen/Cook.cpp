/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#include "Cook.hpp"

#include <iostream>

#include "Kitchen.hpp"

kitchen::Cook::Cook(Kitchen& kitchen, uint maxPizzas)
    : _kitchen(kitchen),
      _state(Waiting),
      _working(true),
      _thread(&Cook::cook, this),
      _maxPizzas(maxPizzas)
{
}

kitchen::Cook::~Cook()
{
    this->_working = false;

    this->_thread.join();
}

kitchen::CookState kitchen::Cook::getState() const
{
    return this->_state;
}

bool kitchen::Cook::handle(const pizza::IPizza::pointer& pizza)
{
    if (this->_pizzas.size() >= this->_maxPizzas)
        return false;

    this->_pizzas.push_back(pizza);

    return true;
}

void kitchen::Cook::cook()
{
    while (this->_working || !this->_pizzas.empty()) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(1)); // TODO: Investigate

        if (this->_pizzas.empty())
            continue;

        const auto& pizza = this->_pizzas.front();
        auto& storage = this->_kitchen.getStorage();

        if (!storage.hasIngredients(pizza->getIngredients()))
            continue;

        this->_state = CookState::Cooking;

        std::cout << this->_thread.get_id() << " says: I'm cooking!"
                  << std::endl;

        storage.removeIngredients(pizza->getIngredients());

        std::this_thread::sleep_for(pizza->getCookTime());

        this->_pizzas.pop_front();

        std::cout << this->_thread.get_id() << " says: Done!" << std::endl;

        if (this->_pizzas.empty())
            this->_state = CookState::Waiting;
    }
}
