/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <utility>

#include "process/Process.hpp"
#include "thread/Print.hpp"

kitchen::Kitchen::Kitchen(
    const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender)
    : _settings(settings), _storage(ingredients), _waiter(receiver, sender), _state(Working)
{
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::Kitchen(): start"
                    << std::endl; // TODO: Remove

    for (unsigned int i = 0; i < settings.cooks; ++i)
        this->_cooks.emplace_back(*this);

    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::Kitchen(): end"
                    << std::endl; // TODO: Remove
}

kitchen::Kitchen::~Kitchen()
{
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::~Kitchen(): start"
                    << std::endl; // TODO: Remove

    this->_cooks.clear();

    this->_waiter.close();

    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::~Kitchen(): end"
                    << std::endl; // TODO: Remove
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
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ready(): start"
                    << std::endl; // TODO: Remove

    std::vector<std::string> message = {"PIZZA", pizza.pack()};

    this->_waiter.send(message, 1);

    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ready(): end" << std::endl; // TODO: Remove
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
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::cook(): start"
                    << std::endl; // TODO: Remove

    while (this->_state != State::Finished) {
        pizza::Pizza pizza;

        try {
            pizza = this->ask();
        } catch (std::exception&) {
            continue;
        }

        this->handle(pizza);
    }

    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::cook(): end" << std::endl; // TODO: Remove
}

pizza::Pizza kitchen::Kitchen::ask()
{
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): start" << std::endl; // TODO: Remove

    auto message = this->_waiter.receive(nullptr);

    if (message[0] == "PIZZA") {
        thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): PIZZA received"
                        << std::endl; // TODO: Remove

        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        return pizza;
    } else if (message[0] == "STATUS") {
        thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): STATUS received"
                        << std::endl; // TODO: Remove

        this->status();
    } else if (message[0] == "STOP") {
        thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): STOP received"
                        << std::endl; // TODO: Remove

        this->_state = Finished;
    }

    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): end" << std::endl; // TODO: Remove

    throw std::exception(); // TODO: Custom Error class
}

bool kitchen::Kitchen::handle(pizza::Pizza pizza)
{
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::handle(): start"
                    << std::endl; // TODO: Remove

    this->_cooks.sort([](const Cook& a, const Cook& b) {
        return (a.getPizzas().size() < b.getPizzas().size());
    });

    bool handled = this->_cooks.front().handle(pizza);

    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::handle(): end"
                    << std::endl; // TODO: Remove

    return handled;
}
