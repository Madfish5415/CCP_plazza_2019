/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.cpp
*/

#include "Manager.hpp"

#include "../def/def.hpp"
#include "../thread/Print.hpp"

reception::Manager::Manager(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients)
    : _cooks(cooks), _ingredients(ingredients)
{
}

reception::Manager::~Manager() = default;

void reception::Manager::handle(const pizza::Pizza& pizza)
{
    this->_kitchens.sort([](const process::Kitchen& a, const process::Kitchen& b) {
        return (a.getPizzas() < b.getPizzas());
    });

    if (this->_kitchens.empty() || !this->_kitchens.front().handle(pizza)) {
        this->createKitchen();

        this->_kitchens.back().handle(pizza);
    }
}

void reception::Manager::manage()
{
    while (!this->_kitchens.empty()) {
        this->receivePizza();
        this->updateKitchens();
    }
}

void reception::Manager::status()
{
    for (auto& kitchen : this->_kitchens)
        kitchen.status();
}

void reception::Manager::createKitchen()
{
    static int kitchenID = 0;

    thread::Print() << "[MANAGER] Create new kitchen with local ID: " << kitchenID << std::endl; // TODO: Remove

    const std::string mq1 = "/kitchen" + std::to_string(kitchenID) + "-mq1";
    const std::string mq2 = "/kitchen" + std::to_string(kitchenID) + "-mq2";

    this->_kitchens.emplace_back(this->_cooks, this->_ingredients, mq1, mq2);

    kitchenID++;
}

void reception::Manager::updateKitchens()
{
    auto i = this->_kitchens.begin();

    for (; i != this->_kitchens.end();) {
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = i->getLast() - now;

        if (elapsed.count() >= MAX_KITCHEN_WAITING) {
            thread::Print() << "[MANAGER] Destroy a kitchen " << std::endl; // TODO: Remove

            i = this->_kitchens.erase(i);
        } else
            i++;
    }
}

void reception::Manager::receivePizza()
{
    for (auto& kitchen : this->_kitchens) {
        pizza::Pizza pizza;

        try {
            pizza = kitchen.receive();
        } catch (std::exception&) {
            continue;
        }

        thread::Print() << "[MANAGER] Received a(n) " << pizza.getRecipe().getType() << std::endl;
    }
}
