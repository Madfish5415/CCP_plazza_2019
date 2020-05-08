/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
#define CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP

#include <unistd.h>

#include <chrono>
#include <cstring>
#include <functional>
#include <stdexcept>

namespace process {

class This {
  public:
    static int getId();

  public:
    template<typename R, typename P>
    static void sleepFor(std::chrono::duration<R, P> time) {
        if (time <= time.zero())
            return;

        auto s = std::chrono::duration_cast<std::chrono::seconds>(time);
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(time - s);

        sleep(s.count());
        usleep(us.count());
    }
};

class Process {
  private:
    int _id {};
    int _status {};

  public:
    Process();

    template<typename T, typename... TArgs>
    explicit Process(T&& callable, TArgs&&... args) {
        this->_id = fork();

        if (this->_id == -1)
            throw std::runtime_error(strerror(errno)); // TODO: Custom Error class

        if (this->_id == 0) {
            std::invoke(callable, args...);

            exit(0);
        }
    }

    ~Process();

  public:
    [[nodiscard]] int getId() const;
    [[nodiscard]] int getStatus() const;

  public:
    void join();
};

} // namespace process

#endif // CPP_PLAZZA_2019_SRC_PROCESS_PROCESS_HPP
