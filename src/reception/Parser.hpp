/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Parser.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP

#include <string>

namespace reception {

class Parser {
  public:
    Parser(const std::string& command);
    ~Parser();
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_PARSER_HPP
