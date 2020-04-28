/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <iostream>

#include "Class.hpp"
#include "reception/Process.hpp"

void function(const std::string& user)
{
    std::cout << "Hello, " << user << "!" << std::endl;
}

int main()
{
    auto obj = new Class();
    reception::Process process2(&Class::function, obj);

    obj->messages.emplace_back("Hello,");
    obj->messages.emplace_back("World!");
    obj->loop = false;

    process2.join();

    return 0;
}
