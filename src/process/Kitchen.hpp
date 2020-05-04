/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP

#include <map>
#include <string>

#include "../mq/Waiter.hpp"
#include "../kitchen/Kitchen.hpp"
#include "Process.hpp"

namespace process {

class Kitchen {
  private:
    mq::Waiter _waiter;
    Process _process;
    int _cooks;
    int _pizzas = 0;

  public:
    Kitchen(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients);
    ~Kitchen();

  public:
    int getPizzas() const;

  public:
    pizza::Pizza receive();
    void send(const pizza::Pizza& pizza);
    void status();
};

}

#endif // CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP
