/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Class.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_CLASS_HPP
#define CPP_PLAZZA_2019_SRC_CLASS_HPP

#include <list>
#include <string>

class Class {
  public:
    std::list<std::string> messages;
    bool loop = true;

  public:
    Class() = default;
    ~Class() = default;

  public:
    void function();
};

#endif // CPP_PLAZZA_2019_SRC_CLASS_HPP
