/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#include "Cook.hpp"

#include "Kitchen.hpp"
#include "thread/Print.hpp"

kitchen::Cook::Cook(kitchen::Kitchen& kitchen) : _kitchen(kitchen), _state(Working), _thread(&Cook::cook, this)
{
}

kitchen::Cook::~Cook()
{
    this->_state = State::Finished;

    this->_thread.join();
}

const std::queue<pizza::Pizza>& kitchen::Cook::getPizzas() const
{
    return this->_pizzas;
}

bool kitchen::Cook::handle(pizza::Pizza pizza)
{
    if (this->_state != State::Working)
        return false;
    if (this->_pizzas.size() >= this->_kitchen.getSettings().maxPerCook)
        return false;

    this->_pizzas.push(pizza);

    return true;
}

void kitchen::Cook::status() const
{
    thread::Print print;

    print << "Cook n°" << this->_thread.get_id() << ":" << std::endl;
    print << "Action: ";

    if (this->_pizzas.empty()) {
        print << "Waiting for a pizza" << std::endl;
    } else {
        auto& pizza = this->_pizzas.front();

        print << "Cooking a(n) " << pizza.getSize() << " " << pizza.getRecipe().getType() << std::endl;
    }
}

void kitchen::Cook::cook()
{
    while ((this->_state == State::Working) || !this->_pizzas.empty()) {
        if (this->_pizzas.empty())
            continue;

        auto& pizza = this->_pizzas.front();
        auto& ingredients = pizza.getRecipe().getIngredients();
        auto& storage = this->_kitchen.getStorage();

        if (!storage.removeHas(ingredients))
            continue;

        auto cookTime = pizza.getRecipe().getCookTime();
        auto timeMultiplier = this->_kitchen.getSettings().timeMultiplier;
        auto sleepTime = (unsigned int)((float)(cookTime)*timeMultiplier);

        std::this_thread::sleep_for(std::chrono::milliseconds (sleepTime));

        this->_kitchen.ready(pizza);
        this->_pizzas.pop();
    }
}
