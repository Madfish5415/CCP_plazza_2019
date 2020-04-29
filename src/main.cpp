/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <iostream>

#include "Parser.hpp"

int main() {
    std::string command;

    std::getline(std::cin, command);

    Parser parser(command);

    parser.parse();
}