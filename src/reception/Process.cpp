/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.cpp
*/

#include "Process.hpp"

#include <sys/wait.h>
#include <unistd.h>

reception::Process::~Process() = default;

int reception::Process::get_id() const
{
    return this->_pid;
}

void reception::Process::join()
{
    waitpid(this->_pid, nullptr, 0);
}

void reception::Process::for_sleep(int seconds)
{
    sleep(seconds);
}

void reception::Process::for_usleep(int useconds)
{
    usleep(useconds);
}
