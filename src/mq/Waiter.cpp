/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.cpp
*/

#include "Waiter.hpp"

#include <regex>

#include "Print.hpp"

mq::Waiter::Waiter() = default;

mq::Waiter::Waiter(int receiver, int sender) : _receiver(receiver, 0666), _sender(sender, 0666)
{
}

mq::Waiter::Waiter(int receiver, int sender, int flags)
    : _receiver(receiver, flags | 0666), _sender(sender, flags | 0666)
{
}

mq::Waiter::~Waiter()
{
}

void mq::Waiter::close() const
{
    this->_receiver.close();
    this->_sender.close();
}

std::vector<std::string> mq::Waiter::receive(long *priority) const
{
    std::string string = this->_receiver.receive(priority, IPC_NOWAIT);

    std::string find = string;
    std::regex word(R"(([^\s]+))");
    std::smatch match;
    std::vector<std::string> message;

    while (std::regex_search(find, match, word)) {
        message.push_back(match.str(1));

        find = match.suffix();
    }

    return message;
}

void mq::Waiter::send(const std::vector<std::string> &message, long priority) const
{
    std::string string;

    for (const auto &item : message) {
        if (item != message.front())
            string += " ";
        string += item;
    }

    this->_sender.send(string, priority, 0);
}
