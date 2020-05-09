/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Storage.cpp
*/

#include "Storage.hpp"

#include "thread/Print.hpp"

kitchen::Storage::Storage(std::map<std::string, unsigned int> ingredients) : _ingredients(std::move(ingredients))
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::Storage(): start" << std::endl;
    thread::Print() << "kitchen::Storage::Storage(): end" << std::endl;
#endif
}

kitchen::Storage::~Storage()
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::~Storage(): start" << std::endl;
    thread::Print() << "kitchen::Storage::~Storage(): end" << std::endl;
#endif
}

void kitchen::Storage::add(const std::map<std::string, unsigned int>& ingredients)
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::add(): start" << std::endl;
#endif

    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients)
        this->_ingredients[ingredient.first] += ingredient.second;

#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::add(): end" << std::endl;
#endif
}

bool kitchen::Storage::has(const std::map<std::string, unsigned int>& ingredients)
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::has(): start" << std::endl;
#endif

    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            return false;
        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            return false;
    }

#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::has(): end" << std::endl;
#endif

    return true;
}

void kitchen::Storage::remove(const std::map<std::string, unsigned int>& ingredients)
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::remove(): start" << std::endl;
#endif

    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            throw std::exception(); // TODO: Custom Error class
        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            throw std::exception(); // TODO: Custom Error class

        this->_ingredients[ingredient.first] -= ingredient.second;
    }

#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::remove(): end" << std::endl;
#endif
}

void kitchen::Storage::status()
{
    thread::Print print;

    for (const auto& ingredient : this->_ingredients)
        print << "- " << ingredient.first << " x" << ingredient.second << std::endl;
}
