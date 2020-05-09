/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Print.hpp"

#include "Kitchen.hpp"

#include "kitchen/Kitchen.hpp"

process::Kitchen::Kitchen(
    const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender)
    : _settings(settings), _waiter(receiver, sender, IPC_CREAT), _last(std::chrono::system_clock::now())
{
    thread::Print() << "process::Kitchen::Kitchen(): start" << std::endl; // TODO: Remove

    this->_process = Process([&settings, &ingredients, receiver, sender]() {
        kitchen::Kitchen k(settings, ingredients, sender, receiver);

        k.cook();
    });

    thread::Print() << "process::Kitchen::Kitchen(): end" << std::endl; // TODO: Remove
}

process::Kitchen::~Kitchen()
{
    thread::Print() << "process::Kitchen::~Kitchen(): start" << std::endl; // TODO: Remove

    std::vector<std::string> message = {"STOP"};

    this->_waiter.send(message, 1);

    this->_process.join();
    this->_waiter.close();

    thread::Print() << "process::Kitchen::~Kitchen(): end" << std::endl; // TODO: Remove
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
    thread::Print() << "process::Kitchen::ask(): start" << std::endl; // TODO: Remove

    auto message = this->_waiter.receive(nullptr);

    if (message[0] == "PIZZA") {
        thread::Print() << "process::Kitchen::ask(): PIZZA received" << std::endl; // TODO: Remove

        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        this->_pending -= 1;
        this->_last = std::chrono::system_clock::now();

        thread::Print() << "process::Kitchen::ask(): Pending: " << this->_pending << std::endl; // TODO: Remove

        return pizza;
    }

    thread::Print() << "process::Kitchen::ask(): end" << std::endl; // TODO: Remove

    throw std::exception(); // TODO: Custom Error class
}

bool process::Kitchen::handle(pizza::Pizza pizza)
{
    thread::Print() << "process::Kitchen::handle(): start" << std::endl; // TODO: Remove

    if (this->_pending >= this->_settings.cooks * MAX_PIZZAS) {
        thread::Print() << "process::Kitchen::handle(): Kitchen is saturating" << std::endl; // TODO: Remove

        return false;
    }

    thread::Print() << "process::Kitchen::handle(): Kitchen handle pizza" << std::endl; // TODO: Remove

    std::vector<std::string> message = {"PIZZA", pizza.pack()};

    this->_waiter.send(message, 1);

    thread::Print() << "process::Kitchen::handle(): end" << std::endl; // TODO: Remove

    return true;
}

void process::Kitchen::status() const
{
    thread::Print() << "process::Kitchen::status(): start" << std::endl; // TODO: Remove

    std::vector<std::string> message = {"STATUS"};

    this->_waiter.send(message, 1);

    thread::Print() << "process::Kitchen::status(): end" << std::endl; // TODO: Remove
}
