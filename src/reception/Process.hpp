/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_PROCESS_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_PROCESS_HPP

#include <unistd.h>

#include <iostream>
#include <type_traits>

namespace reception {

class Process {
  private:
    int _pid;

  public:
    template<typename Function, typename T, typename... TArgs>
    explicit Process(Function&& function, T&& instance, TArgs&&... args,
        std::enable_if_t<std::is_member_function_pointer<Function>::value, int> = 0)
    {
        std::cout << "Process as a member function" << std::endl;

        this->_pid = fork();

        if (this->_pid == 0)
            (instance->*function)(args...);
    }

    template<typename Function, typename... TArgs>
    explicit Process(Function&& function, TArgs&&... args)
    {
        std::cout << "Process as a function" << std::endl;

        this->_pid = fork();

        if (this->_pid == 0)
            function(args...);
    }

    ~Process();

  public:
    int get_id() const;

  public:
    void join();
    void for_sleep(int seconds);
    void for_usleep(int useconds);
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_PROCESS_HPP
