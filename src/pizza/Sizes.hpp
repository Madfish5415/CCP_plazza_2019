/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Sizes.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_SIZES_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_SIZES_HPP

#include <set>
#include <string>

namespace pizza {

class Sizes {
  private:
    std::set<std::string> _ingredients;

  public:
    Sizes();
    ~Sizes();

  public:
    bool has(const std::string& ingredient) const;

  public:
    void load(const std::string& path);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_SIZES_HPP
