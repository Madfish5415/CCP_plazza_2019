/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP

#include <map>
#include <string>

#include "Order.hpp"
#include "kitchen/Kitchen.hpp"
#include "kitchen/Settings.hpp"

namespace reception {

class Manager {
    kitchen::Settings _settings;
    std::map<std::string, unsigned int> _ingredients;
    std::list<kitchen::Kitchen> _kitchens;
    std::map<unsigned int, Order> _orders;
    std::thread _thread;

  public:
    Manager(const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients);
    ~Manager();

  public:
    void handle(const Order& order);
    void status() const;

  public:
    void createKitchen();
    void updateKitchens();
    void updateOrders();

  private:
    void manage();
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
