/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <iostream>
#include <sstream>

#include "../process/Process.hpp"

kitchen::Kitchen::Kitchen(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients,
    const std::string& receiver, const std::string& sender)
    : _storage(ingredients), _receiver(receiver, O_RDONLY), _sender(sender, O_WRONLY), _state(Working)
{
    for (unsigned int i = 0; i < cooks; ++i)
        this->_cooks.emplace_back(*this);
}

kitchen::Kitchen::~Kitchen() {
    std::cout << "Test" << std::endl;

    for (auto &cook : this->_cooks)
        cook.wait();

    this->_receiver.close();
    this->_sender.close();
};

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

void kitchen::Kitchen::ready(const pizza::Pizza& pizza)
{
    this->send(pizza);
}

void kitchen::Kitchen::status() const
{
    std::cout << "Kitchen n°" << process::Process::thisId() << ":" << std::endl;
    std::cout << "Cooks:" << std::endl;

    for (const auto& cook : this->_cooks)
        cook.status();

    std::cout << "Storage:" << std::endl;
    this->_storage.status();
}

pizza::Pizza kitchen::Kitchen::receive()
{
    std::string message = this->_receiver.receiveMessage(nullptr);
    std::istringstream stream(message);
    std::string code;

    std::getline(stream, code, ' ');

    std::cout << "message: " << message << std::endl;
    std::cout << "code: " << code << std::endl;

    if (code == "PIZZA") {
        std::string data;
        pizza::Pizza pizza;

        std::getline(stream, data, ' ');

        std::cout << "data: " << data << std::endl;

        pizza.unpack(data);

        return pizza;
    } else if (code == "STATUS") {
        this->status();
    } else if (code == "STOP") {
        this->_state = State::Finished;
    }

    throw std::exception(); // TODO: Temporary, for testing only
}

void kitchen::Kitchen::send(const pizza::Pizza& pizza)
{
    std::string message = pizza.pack();

    this->_sender.sendMessage(message, 0);
}
