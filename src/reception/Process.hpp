/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_PROCESS_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_PROCESS_HPP

namespace reception {

class Process {
  private:
    int _pid;

  public:
    template<typename Function, typename... TArgs>
    explicit Process(Function&& function, TArgs&&... args);
    ~Process();

  public:
    int get_id();

  public:
    void join();
    void sleep(int seconds);
    void usleep(int microseconds);
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_PROCESS_HPP
