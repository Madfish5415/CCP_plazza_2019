/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Input.cpp
*/

#include "Input.hpp"

#include <iostream>

void reception::Input::clear()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string reception::Input::get()
{
    std::string input;

    while (!std::getline(std::cin, input)) {
        if (std::cin.fail())
            continue;

        Input::clear();
    }

    return input;
}
