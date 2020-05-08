/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Factory.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_FACTORY_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_FACTORY_HPP

#include <memory>

#include "Pizza.hpp"

namespace pizza {

class Factory {
    static std::shared_ptr<Pizza> create(const std::string& recipe, const std::string& size, unsigned int order);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_FACTORY_HPP
