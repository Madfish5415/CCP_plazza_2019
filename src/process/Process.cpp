/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.cpp
*/

#include "Process.hpp"

#include <wait.h>

process::Process::Process() = default;

process::Process::~Process() = default;

int process::Process::getId() const
{
    return this->_pid;
}

int process::Process::getStatus() const
{
    return this->_status;
}

bool process::Process::isChild() const
{
    return this->_child;
}

void process::Process::join()
{
    if (waitpid(this->_pid, &this->_status, 0) == CODE_INVALID)
        throw std::runtime_error(strerror(errno)); // TODO: Custom Error class
}

int process::Process::thisId()
{
    return getpid();
}

void process::Process::forSleep(unsigned int seconds)
{
    sleep(seconds);
}

void process::Process::forUSleep(unsigned int uSeconds)
{
    usleep(uSeconds);
}
