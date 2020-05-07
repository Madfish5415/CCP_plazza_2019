/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP

#include <list>

#include "../mq/Waiter.hpp"
#include "../pizza/Pizza.hpp"
#include "Cook.hpp"
#include "Storage.hpp"

namespace kitchen {

class Kitchen {
  public:
    enum State { Working, Finished };

  private:
    Storage _storage;
    mq::Waiter _waiter;
    State _state;
    std::list<Cook> _cooks {};

  public:
    Kitchen(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender);
    ~Kitchen();

  public:
    Storage& getStorage();

  public:
    void cook();
    bool handle(const pizza::Pizza& pizza);
    void ready(pizza::Pizza pizza);
    void status() const;

  private:
    pizza::Pizza receive();
    void send(const pizza::Pizza& pizza);
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
