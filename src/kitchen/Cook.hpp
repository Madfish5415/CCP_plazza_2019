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

#include <thread>
#include <list>

#include "pizza/IPizza.hpp"

namespace kitchen {

enum CookState { Waiting, Cooking };

class Cook {
  public:
    Kitchen& _kitchen;
    CookState _state;
    bool _working;
    std::thread _thread;
    std::list<pizza::IPizza::pointer> _pizzas {};
    uint _maxPizzas;

  public:
    explicit Cook(Kitchen& kitchen, uint maxPizzas);
    ~Cook();

  public:
    CookState getState() const;

  public:
    bool handle(const pizza::IPizza::pointer& pizza);

  private:
    void cook();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_COOK_HPP
