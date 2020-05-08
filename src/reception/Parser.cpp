/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

#include <regex>

#include "pizza/Factory.hpp"

std::shared_ptr<reception::Order> reception::Parser::parse(const std::string& command)
{
    auto order = std::make_shared<Order>();
    auto subCommands = Parser::toSubCommands(command);

    order->id = Parser::_order++;

    for (const auto& subCommand : subCommands)
        Parser::fill(order, subCommand);

    return order;
}

void reception::Parser::fill(std::shared_ptr<Order> order, const std::string& subCommand)
{
    std::regex regex(R"(^\s*([a-zA-Z]+)\s+([A-Z]+)\s+x([1-9][0-9]*)\s*$)");
    std::smatch matches;

    if (!std::regex_search(subCommand, matches, regex))
        throw std::exception(); // TODO: Custom Error class
    if (matches.size() != 4)
        throw std::exception(); // TODO: Custom Error class

    unsigned int amount = std::stoi(matches.str(3));

    for (unsigned int i = 0; i < amount; ++i) {
        auto pizza = pizza::Factory::create(matches.str(1), matches.str(2), Parser::_order);

        order->pizzas.push_back(pizza);
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
