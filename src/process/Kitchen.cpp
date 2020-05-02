/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <iostream>

process::Kitchen::Kitchen(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients) : _cooks(cooks)
{
    (void)(ingredients);

    std::string receiver = "/receiver";
    std::string sender = "/sender";

    this->_receiver = communication::Waiter(receiver, O_RDONLY);
    this->_sender = communication::Waiter(sender, O_WRONLY);
    this->_process = Process([&cooks, &ingredients, &receiver, &sender]() {
        kitchen::Kitchen k(cooks, ingredients, sender, receiver);

        k.cook();
    });
}

process::Kitchen::~Kitchen()
{
    this->_sender.sendMessage("STOP", 2);

    this->_process.join();
    this->_receiver.close();
    this->_sender.close();
}

int process::Kitchen::getPizzas() const
{
    return this->_pizzas;
}

void process::Kitchen::status()
{
    this->_sender.sendMessage("STATUS", 2);
}

pizza::Pizza process::Kitchen::receive()
{
    std::string message = this->_receiver.receiveMessage(nullptr);
    pizza::Pizza pizza;

    pizza.unpack(message);
    this->_pizzas -= 1;

    return pizza;
}

void process::Kitchen::send(const pizza::Pizza& pizza)
{
    std::string message = "PIZZA " + pizza.pack();

    this->_sender.sendMessage(message, 1);
    this->_pizzas += 1;
}
