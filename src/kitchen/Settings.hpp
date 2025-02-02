/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Settings.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_SETTINGS_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_SETTINGS_HPP

namespace kitchen {

class Settings {
  public:
    float timeMultiplier;
    unsigned int cooks;
    unsigned int refillInterval;
    unsigned int maxPerCook;
    unsigned int maxWaiting;
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_SETTINGS_HPP
