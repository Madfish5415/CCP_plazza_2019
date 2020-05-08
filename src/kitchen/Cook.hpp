/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Cook.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_COOK_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_COOK_HPP

namespace kitchen {
class Kitchen;
}

#include <queue>
#include <thread>

#include "pizza/Pizza.hpp"

namespace kitchen {

class Cook {
  public:
    enum State { Working, Finished };

  private:
    Kitchen& _kitchen;
    State _state;
    std::thread _thread;
    std::queue<std::shared_ptr<pizza::Pizza>> _pizzas;

  public:
    explicit Cook(Kitchen& kitchen);
    ~Cook();

  public:
    const std::queue<std::shared_ptr<pizza::Pizza>>& getPizzas() const;

  public:
    bool handle(const std::shared_ptr<pizza::Pizza> pizza);
    void status() const;

  private:
    void cook();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_COOK_HPP
