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
#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::Manager(): start" << std::endl;
    thread::Print() << "reception::Manager::Manager(): end" << std::endl;
#endif
}

reception::Manager::~Manager()
{
#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::~Manager(): start" << std::endl;
#endif

    this->_state = Finished;

    this->_thread.join();

#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::~Manager(): end" << std::endl;
#endif
}

void reception::Manager::handle(Order order)
{
#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::handle(): start" << std::endl;
#endif

    std::lock_guard<std::mutex> guard(this->_mutex);

    this->_orders.emplace(order.getId(), order);

#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::handle(): Order n°" << order.getId()
                    << " with following pizzas:" << std::endl;

    for (const auto& pizza : order.getPizzas())
        thread::Print() << "- " << pizza.pack() << std::endl;
#endif

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

#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::handle(): end" << std::endl;
#endif
}

void reception::Manager::status()
{
#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::status(): start" << std::endl;
#endif

    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& kitchen : this->_kitchens)
        kitchen.status();

#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::status(): end" << std::endl;
#endif
}

void reception::Manager::manage()
{
#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::manage(): start" << std::endl;
#endif

    while ((this->_state != Finished) || !this->_kitchens.empty()) {
        std::lock_guard<std::mutex> guard(this->_mutex);

        this->updateKitchens();
        this->askKitchens();
        this->updateOrders();
    }

#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::manage(): end" << std::endl;
#endif
}

void reception::Manager::createKitchen()
{
#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::createKitchen(): start" << std::endl;
#endif

    static int receiver = 1;
    static int sender = 2;

    this->_kitchens.emplace_front(this->_settings, this->_ingredients, receiver, sender);

#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::createKitchen(): receiver: " << receiver << ", sender: " << sender
                    << std::endl;
#endif

    receiver += 2;
    sender += 2;

#ifdef LOG_DEBUG
    thread::Print() << "reception::Manager::createKitchen(): end" << std::endl;
#endif
}

void reception::Manager::askKitchens()
{
#ifdef LOG_HARDDEBUG
    thread::Print() << "reception::Manager::askKitchens(): start" << std::endl;
#endif

    for (auto& kitchen : this->_kitchens) {
#ifdef LOG_HARDDEBUG
        thread::Print() << "reception::Manager::askKitchens(): Asking a kitchen..." << std::endl;
#endif

        pizza::Pizza pizza;

        try {
            pizza = kitchen.ask();
        } catch (std::exception&) {
#ifdef LOG_HARDDEBUG
            thread::Print() << "reception::Manager::askKitchens(): No pizza found." << std::endl;
#endif
            continue;
        }

#ifdef LOG_DEBUG
        thread::Print() << "reception::Manager::askKitchens(): Pizza found: " << pizza.pack()
                        << std::endl;
#endif

        auto order = this->_orders[pizza.getOrder()];

        order.ready();

        this->_orders[pizza.getOrder()] = order;

#ifdef LOG_DEBUG
        thread::Print() << "reception::Manager::askKitchens(): Order n°" << order.getId()
                        << ": Pending: " << order.getPending() << std::endl;
#endif
    }
#ifdef LOG_HARDDEBUG
    thread::Print() << "reception::Manager::askKitchens(): end" << std::endl;
#endif
}

void reception::Manager::updateKitchens()
{
#ifdef LOG_HARDDEBUG
    thread::Print() << "reception::Manager::updateKitchens(): start" << std::endl;
#endif

    for (auto i = this->_kitchens.begin(); i != this->_kitchens.end();) {
#ifdef LOG_HARDDEBUG
        thread::Print() << "reception::Manager::updateKitchens(): Updating a kitchen..." << std::endl;
#endif

        if (i->getPending()) {
#ifdef LOG_HARDDEBUG
            thread::Print() << "reception::Manager::updateKitchens(): Kitchen is working" << std::endl;
#endif
            i++;
            continue;
        }

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - i->getLast());

#ifdef LOG_HARDDEBUG
        thread::Print() << "reception::Manager::updateKitchens(): Kitchen has been waiting during " << elapsed.count()
                        << " second(s)" << std::endl;
#endif

        if (elapsed.count() >= MAX_KITCHEN_WAITING) {
#ifdef LOG_DEBUG
            thread::Print() << "reception::Manager::updateKitchens(): Kitchen waiting for too long, erasing it..."
                            << std::endl;
#endif
            i = this->_kitchens.erase(i);
        } else
            i++;
    }

#ifdef LOG_HARDDEBUG
    thread::Print() << "reception::Manager::updateKitchens(): end" << std::endl;
#endif
}

void reception::Manager::updateOrders()
{
#ifdef LOG_HARDDEBUG
    thread::Print() << "reception::Manager::updateOrders(): start" << std::endl;
#endif

    for (auto i = this->_orders.begin(); i != this->_orders.end();) {
#ifdef LOG_HARDDEBUG
        thread::Print() << "reception::Manager::updateOrders(): Order n°" << i->first
                        << ": Pending: " << i->second.getPending() << std::endl;
#endif

        if (!i->second.isComplete()) {
#ifdef LOG_HARDDEBUG
            thread::Print() << "reception::Manager::updateOrders(): Order not yet ready" << std::endl;
#endif
            i++;
            continue;
        }

        i->second.display();

#ifdef LOG_DEBUG
        thread::Print() << "reception::Manager::updateOrders(): Order ready, erasing it..." << std::endl;
#endif

        i = this->_orders.erase(i);
    }

#ifdef LOG_HARDDEBUG
    thread::Print() << "reception::Manager::updateOrders(): end" << std::endl;
#endif
}
