/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Class.cpp
*/

#include "Class.hpp"

#include <iostream>

void Class::function()
{
    while (loop) {
        std::cout << "Loop!" << std::endl;

        if (messages.empty())
            continue;

        std::cout << messages.front() << std::endl;

        messages.pop_front();
    }
}
