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

    std::string mario = "/mario";
    std::string luigi = "/luigi";

    this->_waiter = mq::Waiter(mario, luigi, O_CREAT);
    this->_process = Process([&cooks, &ingredients, &mario, &luigi]() {
        kitchen::Kitchen k(cooks, ingredients, luigi, mario);

        k.cook();
    });
}

process::Kitchen::~Kitchen()
{
    this->_waiter.sendMessage({"STOP"}, 1);

    this->_process.join();
    this->_waiter.close();
}

int process::Kitchen::getPizzas() const
{
    return this->_pizzas;
}

void process::Kitchen::status()
{
    this->_waiter.sendMessage({"STATUS"}, 1);
}

pizza::Pizza process::Kitchen::receive()
{
    std::vector<std::string> message = this->_waiter.receiveMessage(nullptr);

    if (message[0] != "PIZZA")
        throw std::exception(); // TODO: Custom Error class

    pizza::Pizza pizza;

    pizza.unpack(message[1]);
    this->_pizzas -= 1;

    return pizza;
}

void process::Kitchen::send(const pizza::Pizza& pizza)
{
    this->_waiter.sendMessage({"PIZZA", pizza.pack()}, 1);
    this->_pizzas += 1;
}

void process::Kitchen::run()
{
    int counter = 0;

    while (counter != 3) {
        pizza::Pizza pizza;

        try {
            pizza = this->receive();
        } catch (std::exception& e) {
            continue;
        }

        counter++;
    }
}
