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
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Cook::Cook(): start" << std::endl;
    thread::Print() << "kitchen::Cook::Cook(): end" << std::endl;
#endif
}

kitchen::Cook::~Cook()
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Cook::~Cook(): start" << std::endl;
#endif

    this->_state = State::Finished;

    this->_thread.join();

#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Cook::~Cook(): end" << std::endl;
#endif
}

const std::queue<pizza::Pizza>& kitchen::Cook::getPizzas() const
{
    return this->_pizzas;
}

bool kitchen::Cook::handle(pizza::Pizza pizza)
{
#ifdef LOG_DEBUG
    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): start" << std::endl;
#endif

    if (this->_state != State::Working) {
#ifdef LOG_DEBUG
        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): Cook is finishing"
                        << std::endl;
#endif

        return false;
    }

    if (this->_pizzas.size() >= this->_kitchen.getSettings().maxPerCook) {
#ifdef LOG_DEBUG
        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): Cook is saturating"
                        << std::endl;
#endif

        return false;
    }

#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::handle(): Cook handle pizza" << std::endl;
#endif

    this->_pizzas.push(pizza);

#ifdef LOG_DEBUG
    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::handle(): end" << std::endl;
#endif

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
#ifdef LOG_DEBUG
    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): start" << std::endl;
#endif

    while ((this->_state == State::Working) || !this->_pizzas.empty()) {
        if (this->_pizzas.empty())
            continue;

        auto& pizza = this->_pizzas.front();
        auto& ingredients = pizza.getRecipe().getIngredients();
        auto& storage = this->_kitchen.getStorage();

#ifdef LOG_DEBUG
        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): Pizza: " << pizza.pack()
                        << std::endl;
#endif

        if (!storage.removeHas(ingredients)) {
#ifdef LOG_DEBUG
            thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): Not enough ingredients"
                            << std::endl;
#endif

            continue;
        }

        auto cookTime = pizza.getRecipe().getCookTime();
        auto timeMultiplier = this->_kitchen.getSettings().timeMultiplier;
        auto sleepTime = (unsigned int)((float)(cookTime)*timeMultiplier);

#ifdef LOG_DEBUG
        thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): Cook parameters:\n"
                        << "cookTime: " << cookTime << ", timeMultiplier: " << timeMultiplier
                        << ", sleepTime: " << sleepTime << std::endl;
#endif

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

        this->_kitchen.ready(pizza);
        this->_pizzas.pop();
    }

#ifdef LOG_DEBUG
    thread::Print() << "[" << std::this_thread::get_id() << "] kitchen::Cook::cook(): end" << std::endl;
#endif
}
