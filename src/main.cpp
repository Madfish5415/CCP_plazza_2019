/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <vector>

#include "kitchen/Kitchen.hpp"
#include "pizza/Pizza.hpp"

int main()
{
    std::list<pizza::IPizza::pointer> pizzas {};

    pizza::IPizza::Ingredients i1 = {
        {"doe", 1},
        {"tomato", 1},
        {"gruyere", 1},
    };
    auto p1 = std::make_shared<pizza::Pizza>(
        pizza::Margarita, i1, pizza::L, std::chrono::seconds(1));

    pizza::IPizza::Ingredients i2 = {
        {"doe", 1},
        {"tomato", 1},
        {"gruyere", 1},
        {"ham", 1},
        {"mushrooms", 1},
    };
    auto p2 = std::make_shared<pizza::Pizza>(
        pizza::Regina, i2, pizza::L, std::chrono::seconds(2));

    pizza::IPizza::Ingredients i3 = {
        {"doe", 1},
        {"tomato", 1},
        {"gruyere", 1},
        {"steak", 1},
    };
    auto p3 = std::make_shared<pizza::Pizza>(
        pizza::Americana, i3, pizza::L, std::chrono::seconds(2));

    pizza::IPizza::Ingredients i4 = {
        {"doe", 1},
        {"tomato", 1},
        {"gruyere", 1},
        {"eggplant", 1},
        {"goat cheese", 1},
        {"chief love", 1},
    };
    auto p4 = std::make_shared<pizza::Pizza>(
        pizza::Fantasia, i4, pizza::L, std::chrono::seconds(4));

    pizza::IPizza::Ingredients i5 = {
        {"doe", 1},
        {"tomato", 1},
        {"gruyere", 1},
        {"eggplant", 1},
        {"goat cheese", 1},
        {"chief love", 1},
    };
    auto p5 = std::make_shared<pizza::Pizza>(
        pizza::Fantasia, i5, pizza::L, std::chrono::seconds(8));

    pizzas.push_back(p1);
    pizzas.push_back(p2);
    pizzas.push_back(p3);
    pizzas.push_back(p4);
    pizzas.push_back(p5);

    kitchen::Kitchen kitchen(2, 2);

    kitchen.getStorage().addIngredients({
        {"doe", 10},
        {"tomato", 10},
        {"gruyere", 10},
        {"ham", 10},
        {"mushrooms", 10},
        {"steak", 10},
        {"eggplant", 10},
        {"goat cheese", 10},
        {"chief love", 10},
    });

    while (!pizzas.empty()) {
        const auto& pizza = pizzas.front();

        if (kitchen.handle(pizza))
            pizzas.pop_front();
    }

    return 0;
}