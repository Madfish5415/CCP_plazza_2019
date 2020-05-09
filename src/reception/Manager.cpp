/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.cpp
*/

#include "Print.hpp"

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

void reception::Manager::handle(Order order)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    this->_orders.emplace(order.id, order);

    thread::Print() << "=== Handle a order " << order.id << " ===" << std::endl;

    this->_kitchens.sort([](const process::Kitchen& a, const process::Kitchen& b) {
        return (a.getPending() < b.getPending());
    });

    if (this->_kitchens.empty())
        this->createKitchen();

    for (const auto& pizza : order.pizzas) {
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
    thread::Print() << "=== Start managing the plazza ===" << std::endl;

    while (this->_state != Finished) {
        std::lock_guard<std::mutex> guard(this->_mutex);

        this->updateKitchens();
        this->askKitchens();
        this->updateOrders();
    }
}

void reception::Manager::createKitchen()
{
    static int receiver = 1;
    static int sender = 2;

    thread::Print() << "=== Creating a new Kitchen | Receiver: " << receiver << " Sender: " << sender << " ===" << std::endl;

    this->_kitchens.emplace_back(this->_settings, this->_ingredients, receiver, sender);

    receiver += 2;
    sender += 2;
}

void reception::Manager::askKitchens()
{
    for (auto& kitchen : this->_kitchens) {
        pizza::Pizza pizza;

        thread::Print() << "=== Asking kitchens ===" << std::endl;

        try {
            pizza = kitchen.ask();
        } catch (std::exception&) {
            continue;
        }

        thread::Print() << "=== Kitchen has a ready pizza ! ===" << std::endl;

        auto order = this->_orders.at(pizza.getOrder());

        order.ready++;

        thread::Print() << "=== Order n" << order.id << " has " << order.ready << " ready pizzas ===" << std::endl;
    }
}

void reception::Manager::updateKitchens()
{
    thread::Print() << "=== Updating Kitchens ===" << std::endl;
    for (auto i = this->_kitchens.begin(); i != this->_kitchens.end(); ++i) {
        if (i->getPending()) {
            thread::Print() << "=== Kitchen is working on pizzas ===" << std::endl;
            continue;
        }

        thread::Print() << "=== Kitchen is stopped and waiting ===" << std::endl;

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - i->getLast());

        thread::Print() << "=== Elapsed time of the kitchen: " << elapsed.count() << " ===" << std::endl;

        if (elapsed.count() >= MAX_KITCHEN_WAITING) {
            thread::Print() << "=== Erasing a kitchen ===" << std::endl;
            i = --this->_kitchens.erase(i);
        }
    }
}

void reception::Manager::updateOrders()
{
    thread::Print() << "=== Updating Orders === " << std::endl;
    for (const auto& order : this->_orders) {

        thread::Print() << "=== Order n" << order.first << " has " << order.second.ready << " pizzas ===" << std::endl;

        if (order.second.ready != order.second.pizzas.size()) {
            thread::Print() << "=== All the pizzas of the order are not ready yet ! ===" << std::endl;
            continue;
        }

        thread::Print() << "=== All the pizzas are ready man ! ===" << std::endl;

        order.second.display();

        this->_orders.erase(order.first);
    }
}
