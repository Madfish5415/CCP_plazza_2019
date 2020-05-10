/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include "kitchen/Kitchen.hpp"

process::Kitchen::Kitchen(
    const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender)
    : _settings(settings), _waiter(receiver, sender, IPC_CREAT), _last(std::chrono::system_clock::now())
{
#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::Kitchen(): start" << std::endl;
#endif

    this->_process = Process([&settings, &ingredients, receiver, sender]() {
        kitchen::Kitchen k(settings, ingredients, sender, receiver);

        k.cook();
    });

#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::Kitchen(): end" << std::endl;
#endif
}

process::Kitchen::~Kitchen()
{
#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::~Kitchen(): start" << std::endl;
#endif

    std::vector<std::string> message = {"STOP"};

    this->_waiter.send(message, 1);

    this->_process.join();
    this->_waiter.close();

#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::~Kitchen(): end" << std::endl;
#endif
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
#ifdef LOG_HARDDEBUG
    thread::Print() << "process::Kitchen::ask(): start" << std::endl;
#endif

    auto message = this->_waiter.receive(nullptr);

    if (message[0] == "PIZZA") {
#ifdef LOG_DEBUG
        thread::Print() << "process::Kitchen::ask(): PIZZA received" << std::endl;
#endif

        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        this->_pending -= 1;
        this->_last = std::chrono::system_clock::now();

#ifdef LOG_DEBUG
        thread::Print() << "process::Kitchen::ask(): Pending: " << this->_pending << std::endl;
#endif

        return pizza;
    }

#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::ask(): end" << std::endl;
#endif

    throw std::exception(); // TODO: Custom Error class
}

bool process::Kitchen::handle(pizza::Pizza pizza)
{
#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::handle(): start" << std::endl;
#endif

    if (this->_pending >= this->_settings.cooks * this->_settings.maxPerCook) {
#ifdef LOG_DEBUG
        thread::Print() << "process::Kitchen::handle(): Kitchen is saturating" << std::endl;
#endif

        return false;
    }

#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::handle(): Kitchen handle pizza" << std::endl;
#endif

    std::vector<std::string> message = {"PIZZA", pizza.pack()};

    this->_waiter.send(message, 1);
    this->_pending += 1;

#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::handle(): end" << std::endl;
#endif

    return true;
}

void process::Kitchen::status() const
{
#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::status(): start" << std::endl;
#endif

    std::vector<std::string> message = {"STATUS"};

    this->_waiter.send(message, 1);

#ifdef LOG_DEBUG
    thread::Print() << "process::Kitchen::status(): end" << std::endl;
#endif
}
