/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include "Print.hpp"
#include "kitchen/Kitchen.hpp"

process::Kitchen::Kitchen(
    const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender)
    : _settings(settings), _waiter(receiver, sender, IPC_CREAT), _last(std::chrono::system_clock::now())
{
    this->_process = Process([&settings, &ingredients, receiver, sender]() {
        kitchen::Kitchen k(settings, ingredients, sender, receiver);

        k.cook();
    });
}

process::Kitchen::~Kitchen()
{
    std::vector<std::string> message = {"STOP"};

    this->_waiter.send(message, 1);

    this->_process.join();
    this->_waiter.close();
}

unsigned int process::Kitchen::getPending() const
{
    return this->_pending;
}

std::chrono::time_point<std::chrono::system_clock> process::Kitchen::getLast() const
{
    return this->_last;
}

pizza::Pizza process::Kitchen::ask()
{
    auto message = this->_waiter.receive(nullptr);

    if (message[0] == "PIZZA") {
        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        this->_pending -= 1;
        this->_last = std::chrono::system_clock::now();

        return pizza;
    }

    throw std::exception(); // TODO: Custom Error class
}

bool process::Kitchen::handle(pizza::Pizza pizza)
{
    if (this->_pending >= this->_settings.cooks * MAX_PIZZAS)
        return false;

    std::vector<std::string> message = {"PIZZA", pizza.pack()};

    this->_waiter.send(message, 1);
    this->_pending += 1;

    return true;
}

void process::Kitchen::status() const
{
    std::vector<std::string> message = {"STATUS"};

    this->_waiter.send(message, 1);
}
