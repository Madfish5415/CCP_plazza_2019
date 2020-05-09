/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ErrorManager.hpp
*/

#ifndef CCP_PLAZZA_2019_ERRORMANAGER_HPP
#define CCP_PLAZZA_2019_ERRORMANAGER_HPP

class ErrorManager {
  public:
    static bool check(int argc, char **argv);

  private:
    static bool validMultiplier(char *multiplier);
    static bool validCookPerKitchen(char *cookPerKitchen);
    static bool validRefillTime(char *RefillTime);
};

#endif // CCP_PLAZZA_2019_ERRORMANAGER_HPP
