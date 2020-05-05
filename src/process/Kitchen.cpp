/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <iostream>

#include "../def/def.hpp"
#include "../thread/Print.hpp"

process::Kitchen::Kitchen(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients,
    const std::string& mq1, const std::string& mq2)
    : _cooks(cooks), _waiter(mq1, mq2, O_CREAT)
{
    this->_process = Process([&cooks, &ingredients, &mq1, &mq2]() {
        kitchen::Kitchen k(cooks, ingredients, mq2, mq1);

        k.cook();
    });
}

process::Kitchen::~Kitchen()
{
    this->_waiter.sendMessage({"STOP"}, 1);

    this->_process.join();
    this->_waiter.close();
}

unsigned int process::Kitchen::getPizzas() const
{
    return this->_pizzas;
}

std::chrono::time_point<std::chrono::system_clock> process::Kitchen::getLast() const
{
    return this->_last;
}

bool process::Kitchen::handle(const pizza::Pizza& pizza)
{
    if (this->_pizzas >= this->_cooks * MAX_PIZZAS)
        return false;

    this->send(pizza);

    return true;
}

void process::Kitchen::status()
{
    this->_waiter.sendMessage({"STATUS"}, 1);
}

pizza::Pizza process::Kitchen::receive()
{
    std::vector<std::string> message = this->_waiter.receiveMessage(nullptr);

    if (message[0] == "PIZZA") {
        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        this->_pizzas -= 1;
        this->_last = std::chrono::system_clock::now();

        return pizza;
    }

    throw std::exception(); // TODO: Temporary, for testing only
}

void process::Kitchen::send(const pizza::Pizza& pizza)
{
    this->_waiter.sendMessage({"PIZZA", pizza.pack()}, 1);
    this->_pizzas += 1;
}
