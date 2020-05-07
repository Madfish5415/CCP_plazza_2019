/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Ingredients.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_INGREDIENTS_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_INGREDIENTS_HPP

#include <set>
#include <string>

namespace pizza {

class Ingredients {
  private:
    static std::set<std::string>& _ingredients;

  public:
    static std::set<std::string>& get();
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_INGREDIENTS_HPP
