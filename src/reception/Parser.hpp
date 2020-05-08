/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Parser.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP

#include <memory>
#include <vector>

#include "Order.hpp"

namespace reception {

class Parser {
  private:
    static unsigned int& _order();

  public:
    static Order parse(const std::string& command);

  private:
    static void fill(Order order, const std::string& subCommand);
    static std::vector<std::string> toSubCommands(std::string command);
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP
