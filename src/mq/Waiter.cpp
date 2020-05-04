/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.cpp
*/

#include "Waiter.hpp"

#include <iostream>
#include <regex>

mq::Waiter::Waiter() = default;

mq::Waiter::Waiter(const std::string& receiver, const std::string& sender, int flag)
    : _receiver(receiver, O_RDWR | flag, 0666, {.maxMsg = 10, .maxMsgSize = 8192}),
      _sender(sender, O_RDWR | flag, 0666, {.maxMsg = 10, .maxMsgSize = 8192})
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

    std::cout << count << ") receiver: " << this->_receiver.getName() << std::endl; // TODO: Remove

    std::string string = this->_receiver.receive(priority);
    std::string find = string;
    std::regex word(R"(([^\s]+))");
    std::smatch match;
    std::vector<std::string> message;

    while (std::regex_search(find, match, word)) {
        message.push_back(match.str(1));

        find = match.suffix();
    }

    std::cout << count << ") received: " << string << std::endl; // TODO: Remove
    count++;

    return message;
}

void mq::Waiter::sendMessage(const std::vector<std::string>& message, unsigned int priority)
{
    static int count = 0;

    std::cout << count << ") sender: " << this->_sender.getName() << std::endl; // TODO: Remove

    std::string string;

    for (const auto& item : message) {
        if (item != message.front())
            string += " ";
        string += item;
    }

    this->_sender.send(string, priority);

    std::cout << count << ") sent: " << string << std::endl; // TODO: Remove
    count++;
}
