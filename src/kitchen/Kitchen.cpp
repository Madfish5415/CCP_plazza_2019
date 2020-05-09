/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include "process/Process.hpp"
#include "thread/Print.hpp"

kitchen::Kitchen::Kitchen(
    const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender)
    : _settings(settings), _storage(ingredients), _waiter(receiver, sender), _state(Working)
{
    for (unsigned int i = 0; i < settings.cooks; ++i)
        this->_cooks.emplace_back(*this);
}

kitchen::Kitchen::~Kitchen()
{
    this->_cooks.clear();

    this->_waiter.close();
}

const kitchen::Settings& kitchen::Kitchen::getSettings() const
{
    return this->_settings;
}

kitchen::Storage& kitchen::Kitchen::getStorage()
{
    return this->_storage;
}

void kitchen::Kitchen::ready(pizza::Pizza pizza)
{
    std::vector<std::string> message = {"PIZZA", pizza.pack()};

    this->_waiter.send(message, 1);
}

void kitchen::Kitchen::status()
{
    thread::Print print;

    print << "Kitchen n°" << process::This::getId() << ":" << std::endl;
    print << "Cooks:" << std::endl;

    for (const auto& cook : this->_cooks)
        cook.status();

    print << "Storage:" << std::endl;
    this->_storage.status();
}

void kitchen::Kitchen::cook()
{
    while (this->_state != State::Finished) {
        this->refill();

        pizza::Pizza pizza;

        try {
            pizza = this->ask();
        } catch (std::exception&) {
            continue;
        }

        this->handle(pizza);
    }
}

pizza::Pizza kitchen::Kitchen::ask()
{
    auto message = this->_waiter.receive(nullptr);

    if (message[0] == "PIZZA") {
        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        return pizza;
    } else if (message[0] == "STATUS") {
        this->status();
    } else if (message[0] == "STOP") {
        this->_state = Finished;
    }

    throw std::exception(); // TODO: Custom Error class
}

bool kitchen::Kitchen::handle(pizza::Pizza pizza)
{
    this->_cooks.sort([](const Cook& a, const Cook& b) {
        return (a.getPizzas().size() < b.getPizzas().size());
    });

    bool handled = this->_cooks.front().handle(pizza);

    return handled;
}

void kitchen::Kitchen::refill()
{
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_storage.getLast());

    if (elapsed.count() >= this->_settings.refillInterval)
        this->_storage.refill();
}
