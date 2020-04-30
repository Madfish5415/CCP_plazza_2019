/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Pizza.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP

#include <string>

#include "Recipe.hpp"

namespace pizza {

class Pizza {
  private:
    Recipe _recipe;
    std::string _size;

  public:
    Pizza(Recipe& recipe, std::string size);
    ~Pizza();

  public:
    std::string getSize() const;

  public:
    std::string pack() const;
    void unpack(const std::string& pack) const;
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
