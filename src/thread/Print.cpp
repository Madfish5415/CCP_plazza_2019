/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Print.cpp
*/

#include "Print.hpp"

thread::Print::Print() : _lock(thread::Print::_mutex)
{
}

thread::Print::~Print() = default;
