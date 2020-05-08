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
    thread::Print() << "Cook === I do the best pizzas ! ===" << std::endl;
}

kitchen::Cook::~Cook()
{
    this->_state = State::Finished;

    thread::Print() << "Cook === I had enought of this kitchen... ===" << std::endl;

    this->_thread.join();
}

const std::queue<pizza::Pizza>& kitchen::Cook::getPizzas() const
{
    return this->_pizzas;
}

bool kitchen::Cook::handle(pizza::Pizza pizza)
{
    if (this->_state != State::Working) {
        thread::Print() << "Cook === Cook has finished his work ===" << std::endl;
        return false;
    }
    if (this->_pizzas.size() >= MAX_PIZZAS) {
        thread::Print() << "Cook === Cook has already too much pizzas ===" << std::endl;
        return false;
    }

    thread::Print() << "Cook === Cook accept the pizza ===" << std::endl;

    this->_pizzas.push(pizza);

    return true;
}

void kitchen::Cook::status() const
{
    thread::Print print;

    print << "Cook n°" << this->_thread.get_id() << ":" << std::endl;
    print << "Action: ";

    if (this->_pizzas.empty()) {
        print << "Waiting for a pizza" << std::endl;;
    } else {
        auto& pizza = this->_pizzas.front();

        print << "Cooking a(n) " << pizza.getSize() << " " << pizza.getRecipe().getType() << std::endl;
    }

    print << std::endl;
}

void kitchen::Cook::cook()
{
    thread::Print() << "Cook === Start cooking new pizzas ! ===" << std::endl;
    while ((this->_state == State::Working) || !this->_pizzas.empty()) {
        if (this->_pizzas.empty())
            continue;

        thread::Print() << "Cook === A pizza is in preparation ===" << std::endl;
        auto& pizza = this->_pizzas.front();
        auto& ingredients = pizza.getRecipe().getIngredients();
        auto& storage = this->_kitchen.getStorage();

        if (!storage.has(ingredients)) {
            storage.status();
            thread::Print() << "Cook === Fuck there is no more ingredients... ===" << std::endl;
            continue;
        }

        storage.remove(ingredients);

        auto cookTime = pizza.getRecipe().getCookTime();
        auto timeMultiplier = this->_kitchen.getSettings().timeMultiplier;
        auto sleepTime = (unsigned int)((float)(cookTime) * timeMultiplier);

        thread::Print() << "Cook === The pizza is in the hoven ===" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));

        this->_kitchen.ready(pizza);
        this->_pizzas.pop();
    }
}
