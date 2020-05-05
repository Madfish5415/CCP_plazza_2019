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

mq::Waiter::Waiter(const std::string& receiver, const std::string& sender, int flag)
    : _receiver(receiver, O_RDWR | O_NONBLOCK | flag, 0666, {.maxMsg = 10, .maxMsgSize = 8192}),
      _sender(sender, O_RDWR | O_NONBLOCK | flag, 0666, {.maxMsg = 10, .maxMsgSize = 8192})
{
}

mq::Waiter::~Waiter() = default;

void mq::Waiter::close()
{
    this->_receiver.close();
    this->_sender.close();
}

std::vector<std::string> mq::Waiter::receiveMessage(unsigned int* priority)
{
    static int count = 0;

    std::string string = this->_receiver.receive(priority);
    std::string find = string;
    std::regex word(R"(([^\s]+))");
    std::smatch match;
    std::vector<std::string> message;

    while (std::regex_search(find, match, word)) {
        message.push_back(match.str(1));

        find = match.suffix();
    }

    thread::Print() << "[WAITER-" << count << "] Receiver: " << this->_receiver.getName() << std::endl; // TODO: Remove
    thread::Print() << "[WAITER-" << count << "] Received: " << string << std::endl; // TODO: Remove
    count++;

    return message;
}

void mq::Waiter::sendMessage(const std::vector<std::string>& message, unsigned int priority)
{
    static int count = 0;

    std::string string;

    for (const auto& item : message) {
        if (item != message.front())
            string += " ";
        string += item;
    }

    this->_sender.send(string, priority);

    thread::Print() << "[WAITER-" << count << "] Sender: " << this->_sender.getName() << std::endl; // TODO: Remove
    thread::Print() << "[WAITER-" << count << "] Sent: " << string << std::endl; // TODO: Remove
    count++;
}