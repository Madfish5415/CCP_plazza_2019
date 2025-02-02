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

std::chrono::time_point<std::chrono::system_clock> kitchen::Storage::getLast()
{
    return this->_last;
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

bool kitchen::Storage::removeHas(const std::map<std::string, unsigned int>& ingredients)
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::removeHas(): start" << std::endl;
#endif

    std::lock_guard<std::mutex> guard(this->_mutex);

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0) {
#ifdef LOG_DEBUG
            thread::Print() << "kitchen::Storage::removeHas(): Ingredient not found" << std::endl;
#endif

            return false;
        }

        if (this->_ingredients.at(ingredient.first) < ingredient.second) {
#ifdef LOG_DEBUG
            thread::Print() << "kitchen::Storage::removeHas(): Not enougth ingredients" << std::endl;
#endif

            return false;
        }
    }

    for (const auto& ingredient : ingredients) {
        if (this->_ingredients.count(ingredient.first) == 0)
            throw std::exception(); // TODO: Custom Error class
        if (this->_ingredients.at(ingredient.first) < ingredient.second)
            throw std::exception(); // TODO: Custom Error class

        this->_ingredients[ingredient.first] -= ingredient.second;
    }

#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::removeHas(): end" << std::endl;
#endif

    return true;
}

void kitchen::Storage::refill()
{
#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::refill(): start" << std::endl;
#endif

    std::lock_guard<std::mutex> guard(this->_mutex);

    for (auto& ingredient : this->_ingredients)
        ingredient.second += 1;

    this->_last = std::chrono::system_clock::now();

#ifdef LOG_DEBUG
    thread::Print() << "kitchen::Storage::refill(): end" << std::endl;
#endif
}

void kitchen::Storage::status()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    thread::Print print;

    for (const auto& ingredient : this->_ingredients)
        print << "- " << ingredient.first << " x" << ingredient.second << std::endl;
}
