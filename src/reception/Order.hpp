/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Order.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_ORDER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_ORDER_HPP

#include <memory>
#include <list>

#include "pizza/Pizza.hpp"

namespace reception {

class Order {
  private:
    unsigned int _id;
    std::list<pizza::Pizza> _pizzas;
    unsigned int _ready;

  public:
    explicit Order();
    ~Order();

  public:
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] const std::list<pizza::Pizza>& getPizzas() const;
    [[nodiscard]] unsigned int getPending() const;
    [[nodiscard]] bool isComplete() const;

  public:
    void add(pizza::Pizza pizza);
    void display() const;
    void ready();

  private:
    static unsigned int id();
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_ORDER_HPP
