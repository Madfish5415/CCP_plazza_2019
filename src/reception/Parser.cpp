/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

#include <regex>

#include "pizza/Factory.hpp"

reception::Order reception::Parser::parse(const std::string& command)
{
    Order order;
    auto subCommands = Parser::toSubCommands(command);

    for (const auto& subCommand : subCommands)
        Parser::fill(order, subCommand);

    return order;
}

void reception::Parser::fill(Order order, const std::string& subCommand)
{
    std::regex regex(R"(^\s*([a-zA-Z]+)\s+([A-Z]+)\s+x([1-9][0-9]*)\s*$)");
    std::smatch matches;

    if (!std::regex_search(subCommand, matches, regex))
        throw std::exception(); // TODO: Custom Error class
    if (matches.size() != 4)
        throw std::exception(); // TODO: Custom Error class

    unsigned int amount = std::stoi(matches.str(3));

    for (unsigned int i = 0; i < amount; ++i) {
        auto pizza = pizza::Factory::create(matches.str(1), matches.str(2), order.getId());

        order.add(pizza);
    }
}

std::vector<std::string> reception::Parser::toSubCommands(std::string command)
{
    std::vector<std::string> subCommands;
    std::string delimiter = ";";
    std::size_t pos;

    while ((pos = command.find(delimiter)) != std::string::npos) {
        std::string subCommand = command.substr(0, pos);

        subCommands.push_back(subCommand);

        command.erase(0, pos + delimiter.length());
    }

    return subCommands;
}
