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
    thread::Print() << "Kitchen Proc === Creating new kitchen ===" << std::endl;
    for (unsigned int i = 0; i < settings.cooks; ++i)
        this->_cooks.emplace_back(*this);
}

kitchen::Kitchen::~Kitchen()
{
    this->_cooks.clear();

    thread::Print() << "Kitchen Proc === The fire is in the kitchen shut it down ! ===" << std::endl;

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

    thread::Print() << "Kitchen Proc === Pizza is ready ! ===" << std::endl;

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
    thread::Print() << "Kitchen Proc === Cooking a pizza ===" << std::endl;
    while (this->_state != State::Finished) {
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

    thread::Print() << "Kitchen Proc === Looking for new messages... ===" << std::endl;

    if (message[0] == "PIZZA") {
        pizza::Pizza pizza;

        thread::Print() << "Kitchen Proc === Pizza received ===" << std::endl;

        pizza.unpack(message[1]);

        return pizza;
    } else if (message[0] == "STATUS") {
        thread::Print() << "Kitchen Proc === Status asked ===" << std::endl;

        this->status();
    } else if (message[0] == "STOP") {
        thread::Print() << "Kitchen Proc === It's time for me leave you... ===" << std::endl;

        this->_state = Finished;
    }

    thread::Print() << "Kitchen Proc === WTF is this message ? ===" << std::endl;
    throw std::exception(); // TODO: Custom Error class

}

bool kitchen::Kitchen::handle(pizza::Pizza pizza)
{
    this->_cooks.sort([](const Cook& a, const Cook& b) {
        return (a.getPizzas().size() < b.getPizzas().size());
    });

    thread::Print() << "Kitchen Proc === New pizza for the coook ===" << std::endl;

    return this->_cooks.front().handle(pizza);
}
