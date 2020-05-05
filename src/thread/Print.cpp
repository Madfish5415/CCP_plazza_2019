/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Print.cpp
*/

#include "Print.hpp"

thread::Print::Print() : _lock(thread::Print::mutex())
{
}

thread::Print::~Print() = default;

thread::Print &thread::Print::operator<<(std::ostream &(*os)(std::ostream &))
{
    std::cout << os;

    return *this;
}

std::recursive_mutex &thread::Print::mutex()
{
    static std::recursive_mutex mutex;

    return mutex;
}
