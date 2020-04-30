/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP

#include <list>

#include "../pizza/Pizza.hpp"
#include "Cook.hpp"
#include "Storage.hpp"

namespace kitchen {

class Kitchen {
  private:
    std::list<Cook> _cooks;
    Storage _storage;

  public:
    Kitchen(uint cooks, int maxPizzasPerCook, const std::map<std::string, int>& initIngredients);
    ~Kitchen();

  public:
    Storage& getStorage();

  public:
    bool handle(const pizza::Pizza::pointer& pizza);

  private:
    void cook();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
