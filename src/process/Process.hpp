/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
#define CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP

#include <unistd.h>

#include <type_traits>

namespace process {

class Process {
  private:
    int _pid;

  public:
    template<typename F, typename T, typename... TArgs,
        std::enable_if_t<std::is_member_function_pointer<F>::value, int> = 0>
    Process(F&& function, T&& instance, TArgs&&... args)
    {
        this->_pid = fork();

        if (this->_pid == 0)
            (instance->*function)(args...);
    }

    template<typename F, typename... TArgs>
    explicit Process(F&& function, TArgs&&... args)
    {
        this->_pid = fork();

        if (this->_pid == 0)
            function(args...);
    }

    ~Process();

  public:
    int get_id() const;

  public:
    void join();

  public:
    static void for_sleep(int seconds);
    static void for_usleep(int seconds);
};

} // namespace process

#endif // CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
