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
    unsigned int _order {};

  public:
    Pizza();
    Pizza(const Recipe& recipe, std::string  size, unsigned int order);
    ~Pizza();

  public:
    [[nodiscard]] const Recipe& getRecipe() const;
    [[nodiscard]] std::string getSize() const;
    [[nodiscard]] unsigned int getOrder() const;

  public:
    [[nodiscard]] std::string pack() const;
    void unpack(const std::string& pack);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
