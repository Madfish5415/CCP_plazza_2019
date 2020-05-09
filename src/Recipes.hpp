/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Recipes.hpp
*/

#ifndef CCP_PLAZZA_2019_RECIPES_HPP
#define CCP_PLAZZA_2019_RECIPES_HPP

#include <set>
#include <string>
#include <tuple>
#include <map>

class Recipes {
  public:
    Recipes() = delete;
    ~Recipes() = delete;

  public:
    static void load(const std::string& file);
    static bool has(const std::string& name);
    static std::set<std::tuple<std::string, std::map<std::string, unsigned int>, unsigned int>>& get();

  private:
    static std::set<std::tuple<std::string, std::map<std::string, unsigned int>, unsigned int>>& recipes();
    static bool filewatcher(const std::string& path);
};

#endif // CCP_PLAZZA_2019_RECIPES_HPP
