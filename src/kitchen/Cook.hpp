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

#include <list>
#include <thread>

#include "../pizza/IPizza.hpp"

namespace kitchen {

enum CookState { CookWaiting, CookCooking, CookSaturated };

class Cook {
  private:
    Kitchen& _kitchen;
    int _maxPizzas;
    std::thread _thread;
    std::list<pizza::IPizza::pointer> _pizzas;
    CookState _state;
    bool _working;

  public:
    explicit Cook(Kitchen& kitchen, int maxPizzas);
    ~Cook();

  public:
    CookState getState() const;
    bool isWorking() const;

  public:
    bool handle(const pizza::IPizza::pointer& pizza);

  private:
    void cook();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_COOK_HPP
