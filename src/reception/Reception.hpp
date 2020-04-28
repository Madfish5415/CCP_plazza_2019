/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Reception.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_RECEPTION_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_RECEPTION_HPP

#include <list>

#include "../pizza/Pizza.hpp"

namespace reception {

class Reception {
  private:
    Waiter _waiter;
    std::list<pizza::IPizza::pointer> _pizzas;

  public:
    Reception();
    ~Reception();

  public:
    void ready(const pizza::IPizza::pointer& pizza);
};

}

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_RECEPTION_HPP
