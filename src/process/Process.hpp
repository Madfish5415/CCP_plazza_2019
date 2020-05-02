/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
#define CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP

#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <functional>
#include <thread>
#include <type_traits>

#include "../def/def.hpp"

namespace process {

class Process {
  private:
    bool _child = false;
    int _pid = 0;
    int _status = 0;

  public:
    Process();

    template<typename C, typename... TArgs>
    explicit Process(C&& callable, TArgs&&... args)
    {
        this->_pid = fork();

        if (this->_pid == CODE_INVALID)
            throw std::runtime_error(strerror(errno)); // TODO: Custom Error class

        if (this->_pid == 0) {
            this->_child = true;
            this->_pid = getpid();

            std::invoke(callable, args...);

            exit(CODE_SUCCESS);
        }
    }

    ~Process();

  public:
    int getId() const;
    int getStatus() const;
    bool isChild() const;

  public:
    void join();

  public:
    static int thisId();
    static void forSleep(unsigned int seconds);
    static void forUSleep(unsigned int uSeconds);
};

} // namespace process

#endif // CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
