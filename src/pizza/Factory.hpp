/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Factory.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_FACTORY_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_FACTORY_HPP

#include <functional>
#include <map>

#include "IPizza.hpp"

namespace pizza {

class Factory {
  public:
    using Constructor = std::function<IPizza::pointer()>;

  public:
    static IPizza::pointer Create(PizzaType type, PizzaSize size);
    static void Register(PizzaType type, Constructor constructor);

  private:
    static std::map<PizzaType, Constructor> constructors();
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_FACTORY_HPP
