/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

process::Kitchen::Kitchen(
    const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender)
    : _settings(settings), _waiter(receiver, sender, IPC_CREAT)
{
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

std::shared_ptr<pizza::Pizza> process::Kitchen::ask()
{
    std::vector<std::string> message;

    try {
        message = this->_waiter.receive(nullptr);
    } catch (std::exception&) {
        return nullptr;
    }

    if (message[0] == "PIZZA") {
        auto pizza = std::make_shared<pizza::Pizza>();

        pizza->unpack(message[1]);

        this->_pending -= 1;
        this->_last = std::chrono::system_clock::now();

        return pizza;
    }

    return nullptr;
}

bool process::Kitchen::handle(std::shared_ptr<pizza::Pizza> pizza)
{
    if (this->_pending >= this->_settings.cooks * MAX_PIZZAS)
        return false;

    std::vector<std::string> message = {"PIZZA", pizza->pack()};

    this->_waiter.send(message, 1);

    return true;
}

void process::Kitchen::status()
{
    std::vector<std::string> message = {"STATUS"};

    this->_waiter.send(message, 1);
}
