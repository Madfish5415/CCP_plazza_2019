/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ErrorManager.cpp
*/

#include "ErrorManager.hpp"

#include <string>

bool ErrorManager::check(int argc, char **argv)
{
    if (argc != 4)
        return true;

    if (ErrorManager::validMultiplier(argv[1]))
        return true;
    if (ErrorManager::validCookPerKitchen(argv[2]))
        return true;
    if (ErrorManager::validRefillTime(argv[3]))
        return true;

    return false;
}

bool ErrorManager::validMultiplier(char *multiplier)
{
    std::string s(multiplier);

    try {
        float value = std::stof(s);
        return value <= 0;
    } catch (std::exception& e) {
        return true;
    }
}

bool ErrorManager::validCookPerKitchen(char *cookPerKitchen)
{
    std::string s(cookPerKitchen);

    try {
        int value = std::stoi(s);
        return value <= 0;
    } catch (std::exception& e) {
        return true;
    }
}

bool ErrorManager::validRefillTime(char *RefillTime)
{
    std::string s(RefillTime);

    try {
        int value = std::stoi(s);
        return value <= 0;
    } catch (std::exception& e) {
        return true;
    }
}
