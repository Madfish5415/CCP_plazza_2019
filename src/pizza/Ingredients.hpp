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
    std::set<std::string> _ingredients;

  public:
    Ingredients();
    ~Ingredients();

  public:
    bool has(const std::string& ingredient) const;
    std::set<std::string>& get() const;

  public:
    void add(const std::string& ingredient);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_INGREDIENTS_HPP
