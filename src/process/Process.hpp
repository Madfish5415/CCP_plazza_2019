/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
#define CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP

#include <chrono>

namespace process {

class This {
  public:
    static int getId();

  public:
    template<typename R, typename P>
    static void sleepFor(std::chrono::duration<R, P> time);
};

class Process {
  private:
    int _id;
    int _status;

  public:
    Process();
    template<typename T, typename... TArgs>
    explicit Process(T&& callable, TArgs&&... args);
    ~Process();

  public:
    int getId() const;
    int getStatus() const;

  public:
    void join();
};

} // namespace process

#endif // CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
