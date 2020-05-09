/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Process.cpp
*/

#include "Process.hpp"

#include <wait.h>

int process::This::getId()
{
    return getpid();
}

process::Process::Process() = default;

process::Process::~Process() = default;

int process::Process::getId() const
{
    return this->_id;
}

int process::Process::getStatus() const
{
    return this->_status;
}

void process::Process::join()
{
    waitpid(this->_id, &this->_status, 0);
}
