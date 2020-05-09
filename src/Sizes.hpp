/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Size.hpp
*/

#ifndef CCP_PLAZZA_2019_SIZES_HPP
#define CCP_PLAZZA_2019_SIZES_HPP

#include <set>
#include <string>

class Sizes {
  public:
    Sizes() = delete;
    ~Sizes() = delete;

  public:
    static void load(const std::string& file);
    static bool has(const std::string& size);
    static std::set<std::string>& get();

  private:
    static std::set<std::string>& sizes();
    static bool filewatcher(const std::string& path);
};

#endif // CCP_PLAZZA_2019_SIZES_HPP