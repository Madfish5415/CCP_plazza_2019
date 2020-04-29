/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Ingredients.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_INGREDIENTS_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_INGREDIENTS_HPP

#include <string>

namespace pizza {

class Ingredients {
  public:
    Ingredients();
    ~Ingredients();

  public:
    bool has(const std::string& ingredient);

  public:
    void load(const std::string& path);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_INGREDIENTS_HPP
