/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** sender
*/

#include <iostream>
#include "../IPC.hpp"

int main()
{
    IPC sender;
    std::string message;

    while (1) {
        getline(std::cin, message);
        sender.sendMessage(message);
    }
}