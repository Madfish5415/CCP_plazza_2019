/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP

#include <list>

#include "../pizza/IPizza.hpp"
#include "../reception/Process.hpp"
#include "../reception/Waiter.hpp"
#include "Cook.hpp"
#include "Storage.hpp"

namespace kitchen {

enum KitchenState { KitchenWaiting, KitchenCooking, KitchenSaturated };

class Kitchen {
  private:
    std::list<Cook> _cooks;
    Storage _storage;
    KitchenState _state;
    bool _working;
    reception::Process _process;
    reception::Waiter _waiter;

  public:
    Kitchen(int cooks, int maxPizzasPerCook);
    ~Kitchen();

  public:
    KitchenState getState() const;
    Storage& getStorage() const;

  public:
    void ready(const pizza::IPizza::pointer& pizza);

  private:
    void cook();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
