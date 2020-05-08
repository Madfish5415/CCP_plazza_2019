/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Reception.cpp
*/

#include "Reception.hpp"

#include <thread/Print.hpp>
#include <utility>

#include "Input.hpp"
#include "Parser.hpp"

reception::Reception::Reception(const kitchen::Settings& settings, std::map<std::string, unsigned int> ingredients)
    : _manager(settings, std::move(ingredients))
{
}

reception::Reception::~Reception() = default;

void reception::Reception::run()
{
    while (true) {
        std::string command = Input::get();

        thread::Print() << command << std::endl;

        if (command == "status") {
            this->_manager.status();
        } else {
            auto order = Parser::parse(command);

            this->_manager.handle(order);
        }
    }
}
