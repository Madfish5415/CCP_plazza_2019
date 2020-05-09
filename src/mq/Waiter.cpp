/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.cpp
*/

#include "Print.hpp"

#include "Waiter.hpp"

#include <regex>

mq::Waiter::Waiter() = default;

mq::Waiter::Waiter(int receiver, int sender) : _receiver(receiver, 0666), _sender(sender, 0666)
{
    thread::Print() << "mq::Waiter::Waiter(): start" << std::endl; // TODO: Remove
    thread::Print() << "mq::Waiter::Waiter(): end" << std::endl; // TODO: Remove
}

mq::Waiter::Waiter(int receiver, int sender, int flags)
    : _receiver(receiver, flags | 0666), _sender(sender, flags | 0666)
{
    thread::Print() << "mq::Waiter::Waiter(): start" << std::endl; // TODO: Remove
    thread::Print() << "mq::Waiter::Waiter(): end" << std::endl; // TODO: Remove
}

mq::Waiter::~Waiter() {
    thread::Print() << "mq::Waiter::~Waiter(): start" << std::endl; // TODO: Remove
    thread::Print() << "mq::Waiter::~Waiter(): end" << std::endl; // TODO: Remove
}

void mq::Waiter::close() const
{
    thread::Print() << "mq::Waiter::close(): start" << std::endl; // TODO: Remove

    this->_receiver.close();
    this->_sender.close();

    thread::Print() << "mq::Waiter::close(): end" << std::endl; // TODO: Remove
}

std::vector<std::string> mq::Waiter::receive(long *priority) const
{
    std::string string = this->_receiver.receive(priority, IPC_NOWAIT);

    thread::Print() << "mq::Waiter::receive(): Message: " << string << std::endl; // TODO: Remove

    std::string find = string;
    std::regex word(R"(([^\s]+))");
    std::smatch match;
    std::vector<std::string> message;

    while (std::regex_search(find, match, word)) {
        message.push_back(match.str(1));

        find = match.suffix();
    }

    thread::Print() << "mq::Waiter::receive(): end" << std::endl; // TODO: Remove

    return message;
}

void mq::Waiter::send(const std::vector<std::string> &message, long priority) const
{
    std::string string;

    for (const auto& item : message) {
        if (item != message.front())
            string += " ";
        string += item;
    }

    thread::Print() << "mq::Waiter::send(): Message: " << string << std::endl; // TODO: Remove

    this->_sender.send(string, priority, 0);

    thread::Print() << "mq::Waiter::send(): end" << std::endl; // TODO: Remove
}
