/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Reception.cpp
*/

#include "Reception.hpp"

#include <utility>

#include "Input.hpp"
#include "Parser.hpp"
#include "thread/Print.hpp"

reception::Reception::Reception(const kitchen::Settings& settings, std::map<std::string, unsigned int> ingredients)
    : _manager(settings, std::move(ingredients)), _running(true)
{
}

reception::Reception::~Reception() = default;

void reception::Reception::run()
{
    while (this->_running) {
        thread::Print() << "> ";
        std::string command;

        try {
            command = Input::get();
        } catch (std::exception&) {
            break;
        }

        if (command == "exit") {
            break;
        } else if (command == "status") {
            this->_manager.status();
        } else {
            try {
                auto order = Parser::parse(command);

                this->_manager.handle(order);
            } catch (std::exception&) {
                thread::Print() << "Invalid command." << std::endl;
            }
        }
    }
}
