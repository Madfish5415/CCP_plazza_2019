/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.cpp
*/

#include "Waiter.hpp"

#include <regex>

#include "thread/Print.hpp"

mq::Waiter::Waiter() = default;

mq::Waiter::Waiter(int receiver, int sender) : _receiver(receiver, 0666), _sender(sender, 0666)
{
#ifdef LOG_DEBUG
    thread::Print() << "mq::Waiter::Waiter(): start" << std::endl;
    thread::Print() << "mq::Waiter::Waiter(): end" << std::endl;
#endif
}

mq::Waiter::Waiter(int receiver, int sender, int flags)
    : _receiver(receiver, flags | 0666), _sender(sender, flags | 0666)
{
#ifdef LOG_DEBUG
    thread::Print() << "mq::Waiter::Waiter(): start" << std::endl;
    thread::Print() << "mq::Waiter::Waiter(): end" << std::endl;
#endif
}

mq::Waiter::~Waiter() {
#ifdef LOG_DEBUG
    thread::Print() << "mq::Waiter::~Waiter(): start" << std::endl;
    thread::Print() << "mq::Waiter::~Waiter(): end" << std::endl;
#endif
}

void mq::Waiter::close() const
{
#ifdef LOG_DEBUG
    thread::Print() << "mq::Waiter::close(): start" << std::endl;
#endif

    this->_receiver.close();
    this->_sender.close();

#ifdef LOG_DEBUG
    thread::Print() << "mq::Waiter::close(): end" << std::endl;
#endif
}

std::vector<std::string> mq::Waiter::receive(long *priority) const
{
    #ifdef LOG_HARDDEBUG
        thread::Print() << "mq::Waiter::receive(): start" << std::endl;
    #endif

    std::string string = this->_receiver.receive(priority, IPC_NOWAIT);

#ifdef LOG_DEBUG
    thread::Print() << "[" << this->_receiver.getKey() << "] mq::Waiter::receive(): Message: " << string << std::endl;
#endif

    std::string find = string;
    std::regex word(R"(([^\s]+))");
    std::smatch match;
    std::vector<std::string> message;

    while (std::regex_search(find, match, word)) {
        message.push_back(match.str(1));

        find = match.suffix();
    }

#ifdef LOG_DEBUG
    thread::Print() << "[" << this->_receiver.getKey() << "] mq::Waiter::receive(): end" << std::endl;
#endif

    return message;
}

void mq::Waiter::send(const std::vector<std::string> &message, long priority) const
{
#ifdef LOG_HARDDEBUG
    thread::Print() << "mq::Waiter::send(): start" << std::endl;
#endif

    std::string string;

    for (const auto &item : message) {
        if (item != message.front())
            string += " ";
        string += item;
    }

#ifdef LOG_DEBUG
    thread::Print() << "[" << this->_sender.getKey() << "] mq::Waiter::send(): Message: " << string << std::endl;
#endif

    this->_sender.send(string, priority, 0);

#ifdef LOG_DEBUG
    thread::Print() << "[" << this->_sender.getKey() << "] mq::Waiter::send(): end" << std::endl;
#endif
}
