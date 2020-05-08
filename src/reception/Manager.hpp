/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP

#include <list>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#include "Order.hpp"
#include "kitchen/Settings.hpp"
#include "process/Kitchen.hpp"

namespace reception {

class Manager {
  public:
    enum State { Working, Finished };

  private:
    kitchen::Settings _settings;
    std::map<std::string, unsigned int> _ingredients;
    State _state;
    std::thread _thread;
    std::mutex _mutex;
    std::list<process::Kitchen> _kitchens;
    std::map<unsigned int, Order> _orders;

  public:
    Manager(const kitchen::Settings& settings, std::map<std::string, unsigned int> ingredients);
    ~Manager();

  public:
    void handle(const Order& order);
    void status() const;

  private:
    void manage();
    void createKitchen();
    void askKitchens();
    void updateKitchens();
    void updateOrders();
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
