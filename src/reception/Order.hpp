/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Order.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_ORDER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_ORDER_HPP

#include <list>
#include <memory>

#include "pizza/Pizza.hpp"

namespace reception {

class Order {
  public:
    unsigned int id {};
    std::list<std::shared_ptr<pizza::Pizza>> pizzas {};
    unsigned int ready {};

  public:
    Order();
    ~Order();

  public:
    void display() const;
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_ORDER_HPP
