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
    static std::set<std::string>& _sizes();

  public:
    static std::set<std::string>& get();

  public:
    static void load(const std::string& path);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_SIZES_HPP
