/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.cpp
*/

#include "Manager.hpp"

#include <utility>

reception::Manager::Manager(const kitchen::Settings& settings, std::map<std::string, unsigned int> ingredients)
    : _settings(settings), _ingredients(std::move(ingredients)), _state(Working), _thread(&Manager::manage, this)
{
}

reception::Manager::~Manager()
{
    this->_state = Finished;

    this->_thread.join();
}

void reception::Manager::handle(std::shared_ptr<Order> order)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    this->_orders.emplace(order->id, order);

    this->_kitchens.sort([](const process::Kitchen& a, const process::Kitchen& b) {
        return (a.getPending() < b.getPending());
    });

    if (this->_kitchens.empty())
        this->createKitchen();

    for (const auto& pizza : order->pizzas) {
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

    for (const auto& kitchen : this->_kitchens)
        kitchen.status();
}

void reception::Manager::manage()
{
    while (this->_state != Finished) {
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

    this->_kitchens.emplace_back(this->_settings, this->_ingredients, receiver, sender);

    receiver += 2;
    sender += 2;
}

void reception::Manager::askKitchens()
{
    for (auto& kitchen : this->_kitchens) {
        auto pizza = kitchen.ask();

        if (pizza == nullptr)
            continue;

        auto order = this->_orders.at(pizza->getOrder());

        order->ready++;
    }
}

void reception::Manager::updateKitchens()
{
    for (auto i = this->_kitchens.begin(); i != this->_kitchens.end(); ++i) {
        if (i->getPending())
            continue;

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - i->getLast());

        if (elapsed.count() >= MAX_KITCHEN_WAITING)
            i = --this->_kitchens.erase(i);
    }
}

void reception::Manager::updateOrders()
{
    for (const auto& order : this->_orders) {
        if (order.second->ready != order.second->pizzas.size())
            continue;

        order.second->display();

        this->_orders.erase(order.first);
    }
}
