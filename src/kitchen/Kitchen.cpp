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
#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::Kitchen(): start"
                    << std::endl;
#endif

    for (unsigned int i = 0; i < settings.cooks; ++i)
        this->_cooks.emplace_back(*this);

#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::Kitchen(): end"
                    << std::endl;
#endif
}

kitchen::Kitchen::~Kitchen()
{
#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::~Kitchen(): start"
                    << std::endl;
#endif

    this->_cooks.clear();

    this->_waiter.close();

#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::~Kitchen(): end"
                    << std::endl;
#endif
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
#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ready(): start"
                    << std::endl;
#endif

    std::vector<std::string> message = {"PIZZA", pizza.pack()};

    this->_waiter.send(message, 1);

#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ready(): end" << std::endl;
#endif
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
#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::cook(): start"
                    << std::endl;
#endif

    while (this->_state != State::Finished) {
        pizza::Pizza pizza;

        try {
            pizza = this->ask();
        } catch (std::exception&) {
            continue;
        }

        this->handle(pizza);
    }

#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::cook(): end" << std::endl;
#endif
}

pizza::Pizza kitchen::Kitchen::ask()
{
#ifdef LOG_HARDDEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): start" << std::endl;
#endif

    auto message = this->_waiter.receive(nullptr);

    if (message[0] == "PIZZA") {
#ifdef LOG_DEBUG
        thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): PIZZA received"
                        << std::endl;
#endif

        pizza::Pizza pizza;

        pizza.unpack(message[1]);

        return pizza;
    } else if (message[0] == "STATUS") {
#ifdef LOG_DEBUG
        thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): STATUS received"
                        << std::endl;
#endif

        this->status();
    } else if (message[0] == "STOP") {
#ifdef LOG_DEBUG
        thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): STOP received"
                        << std::endl;
#endif

        this->_state = Finished;
    }

#ifdef LOG_HARDDEBUG
    // thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::ask(): end" << std::endl;
#endif

    throw std::exception(); // TODO: Custom Error class
}

bool kitchen::Kitchen::handle(pizza::Pizza pizza)
{
#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::handle(): start"
                    << std::endl;
#endif

    this->_cooks.sort([](const Cook& a, const Cook& b) {
        return (a.getPizzas().size() < b.getPizzas().size());
    });

    bool handled = this->_cooks.front().handle(pizza);

#ifdef LOG_DEBUG
    thread::Print() << "[" << process::This::getId() << "] kitchen::Kitchen::handle(): end"
                    << std::endl;
#endif

    return handled;
}
