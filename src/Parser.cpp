/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

#include <iostream>
#include <regex>

Parser::Parser(const std::string& command) : _command(command)
{
}

Parser::~Parser() = default;

void Parser::parse()
{
    this->fill();
    for (auto& pizza : _pizzaList) {
        try {
            this->checkPizza(pizza);
        } catch (std::exception& e) {
            throw e;
        }
    }
}

void Parser::parse(const std::string& command)
{
    _command = command;
    _pizzaList.clear();
    parse();
}

void Parser::fill()
{
    size_t pos = 0;
    std::string delimiter = ";";
    std::string tmp = _command;

    while ((pos = tmp.find(delimiter)) != std::string::npos) {
        _pizzaList.emplace_back(tmp.substr(0, pos), "", "", 0);
        tmp.erase(0, pos + delimiter.length());
    }
    _pizzaList.emplace_back(tmp, "", "", 0);
}

void Parser::checkPizza(std::tuple<std::string, std::string, std::string, unsigned int>& pizza)
{
    std::regex rgx(R"(^\s*([A-Z][a-z]{2,})\s+([A-Z]+)\s+x([1-9][0-9]*)\s*$)");
    std::smatch matches;

    if (std::regex_search(std::get<0>(pizza), matches, rgx)) {
        if (matches.size() == 4) {
            std::get<1>(pizza) = matches[1].str();
            std::get<2>(pizza) = matches[2].str();
            std::get<3>(pizza) = static_cast<unsigned int>(std::stoi(matches[3].str()));
        } else {
            throw std::exception(); // TODO Create our own exception
        }
    } else {
        throw std::exception(); // TODO Create our own exception
    }
}