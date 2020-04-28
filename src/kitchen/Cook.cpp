/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#include "Cook.hpp"

#include "Kitchen.hpp"

kitchen::Cook::Cook(kitchen::Kitchen& kitchen, int maxPizzas)
    : _kitchen(kitchen),
      _maxPizzas(maxPizzas),
      _thread(&Cook::cook, this),
      _state(CookState::CookWaiting),
      _working(true)
{
}

kitchen::Cook::~Cook()
{
    this->_working = false;

    if (this->_thread.joinable())
        this->_thread.join();
}

kitchen::CookState kitchen::Cook::getState() const
{
    return this->_state;
}

bool kitchen::Cook::isWorking() const
{
    return this->_working;
}

bool kitchen::Cook::handle(const pizza::IPizza::pointer& pizza)
{
    if ((int)(this->_pizzas.size()) >= this->_maxPizzas)
        return false;

    this->_pizzas.push_back(pizza);

    this->_state = CookState::CookCooking;

    if ((int)(this->_pizzas.size()) == this->_maxPizzas)
        this->_state = CookState::CookSaturated;

    return true;
}

void kitchen::Cook::cook()
{
    while (this->_working || !this->_pizzas.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (this->_pizzas.empty())
            continue;

        const auto& pizza = this->_pizzas.front();

        if (!this->_kitchen.getStorage().hasIngredients(pizza->getIngredients()))
            continue;

        this->_kitchen.getStorage().removeIngredients(pizza->getIngredients());

        this->_pizzas.pop_front();

        if (this->_pizzas.empty())
            this->_state = CookState::CookWaiting;
    }
}
