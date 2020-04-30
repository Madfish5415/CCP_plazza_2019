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

#include "../pizza/Pizza.hpp"

namespace kitchen {

class Cook {
  private:
    Kitchen& _kitchen;
    std::thread _thread;
    std::queue<pizza::Pizza::pointer> _pizzas;

  public:
    explicit Cook(Kitchen& kitchen);
    ~Cook();

  public:
    bool handle(const pizza::Pizza::pointer& pizza);

  private:
    void cook();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_COOK_HPP
