/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Sizes.cpp
*/

#include "Sizes.hpp"

#include <fstream>

std::set<std::string>& pizza::Sizes::get()
{
    return Sizes::_sizes;
}

void pizza::Sizes::load(const std::string& path)
{
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line))
        Sizes::_sizes.emplace(line);
}
