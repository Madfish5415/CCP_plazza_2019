/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Parser.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP

#include <memory>

#include "Order.hpp"

namespace reception {

class Parser {
    static std::shared_ptr<Order> parse(const std::string& command);
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP
