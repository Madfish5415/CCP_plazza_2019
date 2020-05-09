/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.cpp
*/

#include "Manager.hpp"

#include <utility>

#include "thread/Print.hpp"

reception::Manager::Manager(const kitchen::Settings& settings, std::map<std::string, unsigned int> ingredients)
    : _settings(settings), _ingredients(std::move(ingredients)), _state(Working), _thread(&Manager::manage, this)
{
}

reception::Manager::~Manager()
{
    this->_state = Finished;

    this->_thread.join();
}

void reception::Manager::handle(Order order)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    this->_orders.emplace(order.getId(), order);

    this->_kitchens.sort([](const process::Kitchen& a, const process::Kitchen& b) {
        return (a.getPending() < b.getPending());
    });

    if (this->_kitchens.empty())
        this->createKitchen();

    for (const auto& pizza : order.getPizzas()) {
        bool handled = this->_kitchens.front().handle(pizza);

        if (!handled) {
            this->createKitchen();

            this->_kitchens.front().handle(pizza);
        }
    }
}

void reception::Manager::status()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    if (this->_kitchens.empty())
        thread::Print() << "No kitchen working." << std::endl;
    for (const auto& kitchen : this->_kitchens)
        kitchen.status();
}

void reception::Manager::manage()
{
    while ((this->_state != Finished) || !this->_kitchens.empty()) {
        std::lock_guard<std::mutex> guard(this->_mutex);

        this->askKitchens();
        this->updateKitchens();
        this->updateOrders();
    }
}

void reception::Manager::createKitchen()
{
    static int receiver = 1;
    static int sender = 2;

    this->_kitchens.emplace_front(this->_settings, this->_ingredients, receiver, sender);

    receiver += 2;
    sender += 2;
}

void reception::Manager::askKitchens()
{
    for (auto& kitchen : this->_kitchens) {
        pizza::Pizza pizza;

        try {
            pizza = kitchen.ask();
        } catch (std::exception&) {
            continue;
        }

        auto order = this->_orders[pizza.getOrder()];

        order.ready();

        this->_orders[pizza.getOrder()] = order;
    }
}

void reception::Manager::updateKitchens()
{
    for (auto i = this->_kitchens.begin(); i != this->_kitchens.end();) {
        if (i->getPending()) {
            i++;
            continue;
        }

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - i->getLast());

        if (elapsed.count() >= this->_settings.maxWaiting) {
            i = this->_kitchens.erase(i);
        } else
            i++;
    }
}

void reception::Manager::updateOrders()
{
    for (auto i = this->_orders.begin(); i != this->_orders.end();) {
        if (!i->second.isComplete()) {
            i++;
            continue;
        }

        i->second.display();

        i = this->_orders.erase(i);
    }
}
