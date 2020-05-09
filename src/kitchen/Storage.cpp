/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Storage.cpp
*/

#include "Storage.hpp"

#include "thread/Print.hpp"

kitchen::Storage::Storage(std::map<std::string, unsigned int> ingredients)
    : _ingredients(std::move(ingredients)), _last(std::chrono::system_clock::now())
{
}

kitchen::Storage::~Storage()
{
}

std::chrono::time_point<std::chrono::system_clock> kitchen::Storage::getLast()
{
    return this->_last;
}

void kitchen::Storage::add(const std::map<std::string, unsigned int>& ingredients)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients)
        this->_ingredients[ingredient.first] += ingredient.second;
}

bool kitchen::Storage::has(const std::map<std::string, unsigned int>& ingredients)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            return false;
        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            return false;
    }

    return true;
}

void kitchen::Storage::remove(const std::map<std::string, unsigned int>& ingredients)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            throw std::exception(); // TODO: Custom Error class
        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            throw std::exception(); // TODO: Custom Error class

        this->_ingredients[ingredient.first] -= ingredient.second;
    }
}

void kitchen::Storage::refill()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (auto& ingredient : this->_ingredients)
        ingredient.second += 1;

    this->_last = std::chrono::system_clock::now();
}

void kitchen::Storage::status()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    thread::Print print;

    for (const auto& ingredient : this->_ingredients)
        print << "- " << ingredient.first << " x" << ingredient.second << std::endl;
}
