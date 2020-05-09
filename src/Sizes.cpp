/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Size.cpp
*/

#include "Sizes.hpp"

#include <fstream>
#include <regex>
#include <filesystem>
#include <iostream>

void Sizes::load(const std::string& path)
{
    std::ifstream file(path);
    std::string line;
    std::regex rgx(R"(^([A-Z]+)$)");
    std::smatch matches;

    if (!Sizes::filewatcher(path)) {
        return;
    }

    Sizes::sizes().clear();

    while (std::getline(file, line)) {
        if (std::regex_search(line, matches, rgx)) {
            Sizes::sizes().emplace(matches[0].str());
        } else {
            std::cerr << "Invalid line in \"" << path << "\" : " << line << std::endl;
        }
    }
}

bool Sizes::has(const std::string& size)
{
    return Sizes::sizes().count(size);
}

std::set<std::string>& Sizes::get()
{
    return Sizes::sizes();
}

std::set<std::string>& Sizes::sizes()
{
    static std::set<std::string> sizes;

    return sizes;
}

bool Sizes::filewatcher(const std::string& path)
{
    static std::string path_to_file;
    static std::filesystem::file_time_type file_time = std::filesystem::last_write_time(path);

    if (path_to_file != path) {
        path_to_file = path;
        file_time = std::filesystem::last_write_time(path);
        return true;
    } else if (file_time != std::filesystem::last_write_time(path)) {
        file_time = std::filesystem::last_write_time(path);
        return true;
    } else {
        return false;
    }
}