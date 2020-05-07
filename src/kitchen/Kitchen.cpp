/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <iostream>

#include "../process/Process.hpp"
#include "../thread/Print.hpp"

kitchen::Kitchen::Kitchen(
    unsigned int cooks, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender)
    : _storage(ingredients), _waiter(receiver, sender), _state(Working)
{
    for (unsigned int i = 0; i < cooks; ++i)
        this->_cooks.emplace_back(*this);
}

kitchen::Kitchen::~Kitchen()
{
    thread::Print() << process::This::getId() << " Kitchen::~Kitchen()" << std::endl; // TODO: Remove

    this->_cooks.clear();

    this->_waiter.close();
}

kitchen::Storage& kitchen::Kitchen::getStorage()
{
    return this->_storage;
}

void kitchen::Kitchen::cook()
{
    while (this->_state != State::Finished) {
        pizza::Pizza pizza;

        try {
            pizza = this->receive();
        } catch (std::exception& e) {
            continue;
        }

        this->handle(pizza);
    }
}

bool kitchen::Kitchen::handle(const pizza::Pizza& pizza)
{
    this->_cooks.sort([](const Cook& a, const Cook& b) {
        return (a.getPizzas().size() < b.getPizzas().size());
    });

    return this->_cooks.front().handle(pizza);
}

void kitchen::Kitchen::ready(pizza::Pizza pizza)
{
    this->send(pizza);
}

void kitchen::Kitchen::status() const
{
    thread::Print print;

    print << "Kitchen n°" << process::This::getId() << ":" << std::endl;
    print << "Cooks:" << std::endl;

    for (const auto& cook : this->_cooks)
        cook.status();

    print << "Storage:" << std::endl;
    this->_storage.status();
}

pizza::Pizza kitchen::Kitchen::receive()
{
    std::vector<std::string> message = this->_waiter.receiveMessage(nullptr);

    if (message[0] == "PIZZA") {
        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        return pizza;
    } else if (message[0] == "STATUS") {
        this->status();
    } else if (message[0] == "STOP") {
        this->_state = State::Finished;
    }

    throw std::exception(); // TODO: Temporary, for testing only
}

void kitchen::Kitchen::send(const pizza::Pizza& pizza)
{
    this->_waiter.sendMessage({"PIZZA", pizza.pack()}, 1);
}
