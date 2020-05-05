/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Print.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_THREAD_PRINT_HPP
#define CPP_PLAZZA_2019_SRC_THREAD_PRINT_HPP

#include <iostream>
#include <mutex>

namespace thread {

class Print {
  private:
    std::unique_lock<std::recursive_mutex> _lock;

  public:
    Print();
    ~Print();

  public:
    template<typename T>
    Print& operator<<(const T& t)
    {
        std::cout << t;

        return *this;
    }

    Print& operator<<(std::ostream& (*os)(std::ostream&));

  public:
    static std::recursive_mutex& mutex();
};

} // namespace thread

#endif // CPP_PLAZZA_2019_SRC_THREAD_PRINT_HPP
