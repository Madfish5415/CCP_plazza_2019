/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.cpp
*/

#include "Waiter.hpp"

#include <iostream>
#include <regex>

#include "../thread/Print.hpp"

mq::Waiter::Waiter() = default;

mq::Waiter::Waiter(int receiver, int sender) : _receiver(receiver, 0666), _sender(sender, 0666)
{
}

mq::Waiter::Waiter(int receiver, int sender, int flags)
    : _receiver(receiver, flags | 0666), _sender(sender, flags | 0666)
{
}

mq::Waiter::~Waiter() = default;

void mq::Waiter::close()
{
    this->_receiver.close();
    this->_sender.close();
}

std::vector<std::string> mq::Waiter::receiveMessage(long* priority)
{
    static int count = 0;

    std::string string = this->_receiver.receive(priority, IPC_NOWAIT);
    std::string find = string;
    std::regex word(R"(([^\s]+))");
    std::smatch match;
    std::vector<std::string> message;

    while (std::regex_search(find, match, word)) {
        message.push_back(match.str(1));

        find = match.suffix();
    }

    thread::Print() << "[WAITER-" << count << "] Receiver: " << this->_receiver.getKey() << std::endl; // TODO: Remove
    thread::Print() << "[WAITER-" << count << "] Received: " << string << std::endl; // TODO: Remove
    count++;

    return message;
}

void mq::Waiter::sendMessage(const std::vector<std::string>& message, long priority)
{
    static int count = 0;

    std::string string;

    for (const auto& item : message) {
        if (item != message.front())
            string += " ";
        string += item;
    }

    this->_sender.send(string, priority, 0);

    thread::Print() << "[WAITER-" << count << "] Sender: " << this->_sender.getKey() << std::endl; // TODO: Remove
    thread::Print() << "[WAITER-" << count << "] Sent: " << string << std::endl; // TODO: Remove
    count++;
}
