/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.cpp
*/

#include "Manager.hpp"

#include <utility>

#include "Print.hpp"

reception::Manager::Manager(const kitchen::Settings& settings, std::map<std::string, unsigned int> ingredients)
    : _settings(settings), _ingredients(std::move(ingredients)), _state(Working), _thread(&Manager::manage, this)
{
    thread::Print() << "reception::Manager::Manager(): start" << std::endl; // TODO: Remove
    thread::Print() << "reception::Manager::Manager(): end" << std::endl; // TODO: Remove
}

reception::Manager::~Manager()
{
    thread::Print() << "reception::Manager::~Manager(): start" << std::endl; // TODO: Remove

    this->_state = Finished;

    this->_thread.join();

    thread::Print() << "reception::Manager::~Manager(): end" << std::endl; // TODO: Remove
}

void reception::Manager::handle(Order order)
{
    thread::Print() << "reception::Manager::handle(): start" << std::endl; // TODO: Remove

    std::lock_guard<std::mutex> guard(this->_mutex);

    this->_orders.emplace(order.getId(), order);

    thread::Print() << "reception::Manager::handle(): Order n°" << order.getId()
                    << " with following pizzas:" << std::endl; // TODO: Remove

    for (const auto& pizza : order.getPizzas())
        thread::Print() << "- " << pizza.pack() << std::endl; // TODO: Remove

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

    thread::Print() << "reception::Manager::handle(): end" << std::endl; // TODO: Remove
}

void reception::Manager::status()
{
    thread::Print() << "reception::Manager::status(): start" << std::endl; // TODO: Remove

    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& kitchen : this->_kitchens)
        kitchen.status();

    thread::Print() << "reception::Manager::status(): end" << std::endl; // TODO: Remove
}

void reception::Manager::manage()
{
    thread::Print() << "reception::Manager::manage(): start" << std::endl; // TODO: Remove

    while ((this->_state != Finished) || !this->_kitchens.empty()) {
        std::lock_guard<std::mutex> guard(this->_mutex);

        this->updateKitchens();
        this->askKitchens();
        this->updateOrders();
    }

    thread::Print() << "reception::Manager::manage(): end" << std::endl; // TODO: Remove
}

void reception::Manager::createKitchen()
{
    thread::Print() << "reception::Manager::createKitchen(): start" << std::endl; // TODO: Remove

    static int receiver = 1;
    static int sender = 2;

    this->_kitchens.emplace_back(this->_settings, this->_ingredients, receiver, sender);

    thread::Print() << "reception::Manager::createKitchen(): receiver: " << receiver << ", sender: " << sender
                    << std::endl; // TODO: Remove

    receiver += 2;
    sender += 2;

    thread::Print() << "reception::Manager::createKitchen(): end" << std::endl; // TODO: Remove
}

void reception::Manager::askKitchens()
{
    // thread::Print() << "reception::Manager::askKitchens(): start" << std::endl; // TODO: Remove

    for (auto& kitchen : this->_kitchens) {
        // thread::Print() << "reception::Manager::askKitchens(): Asking a kitchen..." << std::endl; // TODO: Remove

        pizza::Pizza pizza;

        try {
            pizza = kitchen.ask();
        } catch (std::exception&) {
            // thread::Print() << "reception::Manager::askKitchens(): No pizza found." << std::endl; // TODO: Remove
            continue;
        }

        thread::Print() << "reception::Manager::askKitchens(): Pizza found: " << pizza.pack()
                        << std::endl; // TODO: Remove

        auto order = this->_orders.at(pizza.getOrder());

        order.ready();

        thread::Print() << "reception::Manager::askKitchens(): Order n°" << order.getId()
                        << ": Pending: " << order.getPending() << std::endl; // TODO: Remove
    }

    // thread::Print() << "reception::Manager::askKitchens(): end" << std::endl; // TODO: Remove
}

void reception::Manager::updateKitchens()
{
    // thread::Print() << "reception::Manager::updateKitchens(): start" << std::endl; // TODO: Remove

    for (auto i = this->_kitchens.begin(); i != this->_kitchens.end(); ++i) {
        // thread::Print() << "reception::Manager::updateKitchens(): Updating a kitchen..." << std::endl; // TODO:
        // Remove

        if (i->getPending()) {
            // thread::Print() << "reception::Manager::updateKitchens(): Kitchen is working" << std::endl; // TODO:
            // Remove
            continue;
        }

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - i->getLast());

        thread::Print() << "reception::Manager::updateKitchens(): Kitchen has been waiting during " << elapsed.count()
                        << " second(s)" << std::endl; // TODO: Remove

        if (elapsed.count() >= MAX_KITCHEN_WAITING) {
            thread::Print() << "reception::Manager::updateKitchens(): Kitchen waiting for too long, erasing it..."
                            << std::endl; // TODO: Remove
            i = --this->_kitchens.erase(i);
        }
    }

    // thread::Print() << "reception::Manager::updateKitchens(): end" << std::endl; // TODO: Remove
}

void reception::Manager::updateOrders()
{
    // thread::Print() << "reception::Manager::updateOrders(): start" << std::endl; // TODO: Remove

    for (const auto& order : this->_orders) {
        /*thread::Print() << "reception::Manager::updateOrders(): Order n°" << order.first
                        << ": Ready: " << order.second.ready << std::endl; // TODO: Remove*/

        if (!order.second.isComplete()) {
            // thread::Print() << "reception::Manager::updateOrders(): Order not yet ready" << std::endl;
            continue;
        }

        order.second.display();

        this->_orders.erase(order.first);

        thread::Print() << "reception::Manager::updateOrders(): Order ready, erasing it..." << std::endl;
    }

    // thread::Print() << "reception::Manager::updateOrders(): end" << std::endl; // TODO: Remove
}
