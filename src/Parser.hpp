/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Parser.hpp
*/

#ifndef CCP_PLAZZA_2019_PARSER_HPP
#define CCP_PLAZZA_2019_PARSER_HPP

#include <string>
#include <vector>

class Parser {
  public:
    explicit Parser(const std::string& command);
    ~Parser();

  public:
    void parse();
    void parse(const std::string& command);

  private:
    void fill();
    void checkPizza(std::tuple<std::string, std::string, std::string, unsigned int>& pizza);

  private:
    std::vector<std::tuple<std::string, std::string, std::string, unsigned int>> _pizzaList;
    std::string _command;
};

#endif // CCP_PLAZZA_2019_PARSER_HPP
