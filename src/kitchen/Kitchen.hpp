/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP

#include <list>

#include "Cook.hpp"
#include "Storage.hpp"

namespace kitchen {

class Kitchen {
  private:
    std::list<Cook> _cooks {};
    Storage _storage;

  public:
    Kitchen(uint maxCooks, uint maxPizzasPerCook);
    ~Kitchen();

  public:
    Storage& getStorage() const;

  public:
    bool handle(const pizza::IPizza::pointer& pizza);
    void wait();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
