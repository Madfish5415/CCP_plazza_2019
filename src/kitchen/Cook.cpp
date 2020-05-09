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
    thread::Print() << "kitchen::Cook::Cook(): start" << std::endl; // TODO: Remove
    thread::Print() << "kitchen::Cook::Cook(): end" << std::endl; // TODO: Remove
}

kitchen::Cook::~Cook()
{
    thread::Print() << "kitchen::Cook::~Cook(): start" << std::endl; // TODO: Remove

    this->_state = State::Finished;

    this->_thread.join();

    thread::Print() << "kitchen::Cook::~Cook(): end" << std::endl; // TODO: Remove
}

const std::queue<pizza::Pizza>& kitchen::Cook::getPizzas() const
{
    return this->_pizzas;
}

bool kitchen::Cook::handle(pizza::Pizza pizza)
{
    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): start"
                    << std::endl; // TODO: Remove

    if (this->_state != State::Working) {
        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): Cook is finishing"
                        << std::endl; // TODO: Remove
        return false;
    }
    if (this->_pizzas.size() >= MAX_PIZZAS) {
        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): Cook is saturating"
                        << std::endl; // TODO: Remove
        return false;
    }

    thread::Print() << "process::Kitchen::handle(): Cook handle pizza" << std::endl; // TODO: Remove

    this->_pizzas.push(pizza);

    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): end" << std::endl; // TODO: Remove

    return true;
}

void kitchen::Cook::status() const
{
    thread::Print print;

    print << "Cook n°" << this->_thread.get_id() << ":" << std::endl;
    print << "Action: ";

    if (this->_pizzas.empty()) {
        print << "Waiting for a pizza" << std::endl;
        ;
    } else {
        auto& pizza = this->_pizzas.front();

        print << "Cooking a(n) " << pizza.getSize() << " " << pizza.getRecipe().getType() << std::endl;
    }

    print << std::endl;
}

void kitchen::Cook::cook()
{
    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): start" << std::endl; // TODO: Remove

    while ((this->_state == State::Working) || !this->_pizzas.empty()) {
        if (this->_pizzas.empty())
            continue;

        auto& pizza = this->_pizzas.front();
        auto& ingredients = pizza.getRecipe().getIngredients();
        auto& storage = this->_kitchen.getStorage();

        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): Pizza: " << pizza.pack()
                        << std::endl; // TODO: Remove

        if (!storage.has(ingredients)) {
            thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): Not enough ingredients"
                            << std::endl; // TODO: Remove
            continue;
        }

        storage.remove(ingredients);

        auto cookTime = pizza.getRecipe().getCookTime();
        auto timeMultiplier = this->_kitchen.getSettings().timeMultiplier;
        auto sleepTime = (unsigned int)((float)(cookTime)*timeMultiplier);

        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): Cook parameters:\n"
                        << "cookTime: " << cookTime << ", timeMultiplier: " << timeMultiplier
                        << ", sleepTime: " << sleepTime << std::endl; // TODO: Remove

        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));

        this->_kitchen.ready(pizza);
        this->_pizzas.pop();
    }

    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): end" << std::endl; // TODO: Remove
}
